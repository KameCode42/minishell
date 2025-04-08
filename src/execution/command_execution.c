/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_execution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 20:11:15 by david             #+#    #+#             */
/*   Updated: 2025/04/03 18:15:53 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtins(t_command *cmd)
{
	if (ft_strcmp(cmd->args[0], "cd") == 0
		|| ft_strcmp(cmd->args[0], "env") == 0
		|| ft_strcmp(cmd->args[0], "echo") == 0
		|| ft_strcmp(cmd->args[0], "pwd") == 0
		|| ft_strcmp(cmd->args[0], "exit") == 0
		|| ft_strcmp(cmd->args[0], "export") == 0
		|| ft_strcmp(cmd->args[0], "unset") == 0)
		return (1);
	return (0);
}

void	execute_builtins(t_command *cmd, t_shell *shell)
{
	if (ft_strcmp(cmd->args[0], "cd") == 0)
		execute_cd(shell, cmd);
	else if (ft_strcmp(cmd->args[0], "env") == 0)
		execute_env(shell);
	else if (ft_strcmp(cmd->args[0], "echo") == 0)
		execute_echo(cmd);
	else if (ft_strcmp(cmd->args[0], "pwd") == 0)
		execute_pwd();
	else if (ft_strcmp(cmd->args[0], "exit") == 0)
		execute_exit(shell, cmd);
	else if (ft_strcmp(cmd->args[0], "export") == 0)
		execute_export(shell, cmd);
	else if (ft_strcmp(cmd->args[0], "unset") == 0)
		execute_unset(shell, cmd);
}

void	execute_builtin_with_redir(t_command *cmd, t_shell *shell)
{
	int	saved_stdout;
	int	saved_stdin;

	saved_stdout = dup(STDOUT_FILENO);
	saved_stdin = dup(STDIN_FILENO);
	if (saved_stdout == -1 || saved_stdin == -1)
	{
		perror("dup");
		return ;
	}
	if (handle_redirections(cmd) != 0)
	{
		close(saved_stdout);
		close(saved_stdin);
		return ;
	}
	execute_builtins(cmd, shell);
	if (dup2(saved_stdout, STDOUT_FILENO) == -1)
		perror("dup2 restore stdout");
	if (dup2(saved_stdin, STDIN_FILENO) == -1)
		perror("dup2 restore stdin");
	close(saved_stdout);
	close(saved_stdin);
}

void	execute_external_command(t_shell *shell, t_command *cmd)
{
	char	**path;

	path = find_path(shell);
	if (path == NULL || cmd->args[0] == NULL)
	{
		print_cmd_not_found(cmd);
		if (path)
			free_array(path);
		return ;
	}
	process_cmd(shell, cmd, path);
	free_array(path);
}

void	execute_commands(t_shell *shell)
{
	t_command	*current;

	current = shell->cmds;
	if (current && current->next)
	{
		execute_pipe(shell);
		return ;
	}
	while (current)
	{
		if (current->args && current->args[0])
		{
			if (is_builtins(current))
				execute_builtin_with_redir(current, shell);
			else
				execute_external_command(shell, current);
		}
		current = current->next;
	}
}
