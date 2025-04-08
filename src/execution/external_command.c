/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dle-fur <dle-fur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 08:49:58 by david             #+#    #+#             */
/*   Updated: 2025/04/04 11:32:54 by dle-fur          ###   ########.fr       */
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
//==============================================================================

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

int	exec_relative_path(t_command *cmd, char **tab_env)
{
	if (access(cmd->args[0], F_OK | X_OK) == 0)
	{
		execve(cmd->args[0], cmd->args, tab_env);
		free_env_array(tab_env);
		return (1);
	}
	free_env_array(tab_env);
	return (1);
}

int	exec_path_env(t_command *cmd, char **path, char **tab_env)
{
	int		i;
	char	*cmd_path;
	char	*tmp;

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

int	access_command(t_shell *shell, t_command *cmd, char **path)
{
	char	**tab_env;

	tab_env = convert_env_list(shell);
	if (tab_env == NULL)
		return (1);
	if (cmd->args[0][0] == '/' || ft_strncmp(cmd->args[0], "./", 2) == 0
		|| ft_strncmp(cmd->args[0], "../", 3) == 0)
	{
		return (exec_relative_path(cmd, tab_env));
	}
	return (exec_path_env(cmd, path, tab_env));
}

void	process_cmd(t_shell *shell, t_command *cmd, char **path)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return ;
	if (pid == 0)
	{
		if (handle_redirections(cmd) != 0)
		{
			free_child(shell, path);
			exit (1);
		}
		if (access_command(shell, cmd, path) != 0)
		{
			print_cmd_not_found(cmd);
			free_child(shell, path);
			exit (127);
		}
		exit (0);
	}
	else
		wait_for_children(shell);
}
