/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 08:49:58 by david             #+#    #+#             */
/*   Updated: 2025/03/28 15:04:27 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// =============================================================================
// find_path :
//
// permet de recuperer le chemin PATH dans l'env
// split le chemin pour obtenir -> usr/bin
//
// =============================================================================
// access_command :
//
// permet de savoir si la commande externe est executable
// joint "/" pour obtenir -> usr/bin/ls
// controle si ls existe et si executable
//
// =============================================================================
// process_command :
//
// permet d'initialiser un processus avec fork pour la commande
// si la commande n'existe pas, return une erreur
// sinon attend la fin du processus
//
//=============================================================================
// execute_external_command :
//
// permet d'executer une commande simple commme ls ou ls -l
// recupere le chemin de PATH
// on passe par process pour executer ou non la commande
//
// =============================================================================

void	print_cmd_not_found(t_command *cmd)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd->args[0], 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd("command not found\n", 2);
}

char	**find_path(t_shell *shell)
{
	char	*path;
	char	**f_path;

	path = ft_getenv(shell, "PATH");
	if (path == NULL)
		return (NULL);
	f_path = ft_split(path, ':');
	free(path);
	return (f_path);
}

int	access_command(t_shell *shell, t_command *cmd, char **path)
{
	int		i;
	char	*cmd_path;
	char	*tmp;
	char	**tab_env;

	tab_env = convert_env_list(shell);
	if (tab_env == NULL)
		return (1);
	i = -1;
	while (path[++i] != NULL)
	{
		tmp = ft_strjoin(path[i], "/");
		cmd_path = ft_strjoin(tmp, cmd->args[0]);
		free(tmp);
		if (access(cmd_path, F_OK | X_OK) == 0)
		{
			execve(cmd_path, cmd->args, tab_env);
			free_env_array(tab_env);
			free(cmd_path);
			return (1);
		}
		free(cmd_path);
	}
	free_env_array(tab_env);
	return (1);
}

void	process_cmd(t_shell *shell, t_command *cmd, char **path)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
		return ;
	if (pid == 0)
	{
		if (handle_redirections(cmd) != 0)
			exit(1);
		if (access_command(shell, cmd, path) != 0)
		{
			print_cmd_not_found(cmd);
			exit (127);
		}
		exit (0);
	}
	else
	{
		waitpid(pid, &status, 0);
		handle_child_exit_status(shell, status);
	}
}

void	execute_external_command(t_shell *shell, t_command *cmd)
{
	char	**path;

	path = find_path(shell);
	if (path == NULL || cmd->args[0] == NULL)
	{
		free_array(path);
		return ;
	}
	process_cmd(shell, cmd, path);
	free_array(path);
}
