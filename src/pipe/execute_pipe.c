/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 17:10:36 by dle-fur           #+#    #+#             */
/*   Updated: 2025/04/08 17:39:24 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// =============================================================================
// child_proc :
//
// permet de rediriger la sortie standard vers pipe_fd[1] -> ecriture
// prev_fd sert a sauvegarder la commande precedente
// si une commande next existe on tente de l executer avec access_command
// exemple: ls -l | wc -l
// ls -l -> premiere enfant          wc -l -> deuxieme enfant
// execute wc -l avec les donnees de ls -l
//
// =============================================================================
// parent_proc :
//
// permet de fermer les descripteur inutile
// ferme le pipe_fd[1] ecriture et transmet l'info de pipe_fd[0] a cmd->next
// attend que les processus enfant se termine avec waitpid
//
// =============================================================================
// execute_pipe :
//
// le child ecrit
// le parent recupere et transmet a l'enfant suivant si necessaire
//
// =============================================================================

void	check_redir(t_shell *shell, t_command *cmd, int pipe_fd[2], char **path)
{
	if (handle_redirections(cmd) != 0)
	{
		free_child(shell, path);
		exit(1);
	}
	if (shell->prev_fd != -1)
	{
		if (dup2(shell->prev_fd, STDIN_FILENO) == -1)
			error_dup2(shell->prev_fd, -1, "dup2 prev_fd");
		close(shell->prev_fd);
	}
	if (cmd->next)
	{
		if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
			error_dup2(pipe_fd[1], pipe_fd[0], "dup2 pipe_fd");
		close(pipe_fd[1]);
		close(pipe_fd[0]);
	}
}

void	child_proc(t_shell *shell, t_command *cmd, int pipe_fd[2], char **path)
{
	check_redir(shell, cmd, pipe_fd, path);
	if (access_command(shell, cmd, path) != 0)
	{
		print_cmd_not_found(cmd);
		free_child(shell, path);
		exit (127);
	}
	free_child(shell, path);
	exit(0);
}

void	parent_proc(t_shell *shell, t_command *cmd, int pipe_fd[2])
{
	if (cmd->next)
		close(pipe_fd[1]);
	if (shell->prev_fd != -1)
		close(shell->prev_fd);
	if (cmd->next != NULL)
		shell->prev_fd = pipe_fd[0];
	else
	{
		close(pipe_fd[0]);
		shell->prev_fd = -1;
	}
}

void	execute_pipe(t_shell *shell)
{
	int			pipe_fd[2];
	pid_t		pid;
	char		**path;
	t_command	*cmd;

	cmd = shell->cmds;
	path = find_path(shell);
	if (path == NULL)
		print_cmd_not_found(cmd);
	while (cmd != NULL)
	{
		if (cmd->next && create_pipe(pipe_fd) == -1)
			return ;
		pid = fork();
		if (pid == -1)
			error_fork();
		if (pid == 0)
			child_proc(shell, cmd, pipe_fd, path);
		else
			parent_proc(shell, cmd, pipe_fd);
		cmd = cmd->next;
	}
	wait_for_children(shell);
	free_array(path);
}
