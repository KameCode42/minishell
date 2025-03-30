/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 11:03:36 by aledos-           #+#    #+#             */
/*   Updated: 2025/03/30 14:34:16 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// =============================================================================
// execute_cd
// =============================================================================
//
// redir_cd_no_arg : gestion cd
// redir_cd_tilde : gestion de la commande cd ~ et cd ~/blabla
// redir_cd_dash : gestion cd -
// execute_cd : gestion cd . / cd .. / cd ./blabla / cd ../blabala par chdir
//
// getenv permet de recuperer le chemin designer de l'env
// getcwd permet de stocker le chemin courant
// =============================================================================

static void	handle_cd_error(t_shell *shell, char *path, char *old_pwd)
{
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(path, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	free(path);
	free(old_pwd);
	shell->exit_status = 1;
}

static void	handle_cd_success(t_shell *shell, char *path, char *old_pwd)
{
	update_pwd_env(shell, old_pwd);
	free(old_pwd);
	free(path);
	shell->exit_status = 0;
}

static int	check_cd_errors(t_shell *shell, t_command *cmd, char **old_pwd)
{
	*old_pwd = getcwd(NULL, 0);
	if (*old_pwd == NULL)
	{
		perror("minishell: cd");
		shell->exit_status = 1;
		return (1);
	}
	if (cmd->args[1] && cmd->args[2])
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		free(*old_pwd);
		shell->exit_status = 1;
		return (1);
	}
	return (0);
}

void	execute_cd(t_shell *shell, t_command *cmd)
{
	char	*path;
	char	*old_pwd;

	if (check_cd_errors(shell, cmd, &old_pwd))
		return ;
	path = redir_cd_path(shell, cmd);
	if (path == NULL || chdir(path) != 0)
	{
		if (path != NULL)
			handle_cd_error(shell, path, old_pwd);
		return ;
	}
	handle_cd_success(shell, path, old_pwd);
}
