/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 14:41:17 by aledos-s          #+#    #+#             */
/*   Updated: 2025/03/30 14:31:53 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*redir_cd_no_arg(t_shell *shell)
{
	char	*home;

	home = ft_getenv(shell, "HOME");
	if (home == NULL)
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		return (NULL);
	}
	return (home);
}

char	*redir_cd_tilde(t_shell *shell, t_command *cmd)
{
	char	*home;
	char	*path;

	home = ft_getenv(shell, "HOME");
	if (home == NULL)
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		return (NULL);
	}
	if (cmd->args[1][1] == '\0')
		path = ft_strdup(home);
	else if (cmd->args[1][1] == '/')
		path = ft_strjoin(home, cmd->args[1] + 1);
	else
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(cmd->args[1], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		free(home);
		return (NULL);
	}
	free(home);
	return (path);
}

char	*redir_cd_dash(t_shell *shell)
{
	t_env	*old_pwd;

	old_pwd = find_env_var(shell, "OLDPWD");
	if (old_pwd == NULL)
	{
		ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2);
		return (NULL);
	}
	printf("%s\n", old_pwd->value);
	return (ft_strdup(old_pwd->value));
}

char	*redir_cd_path(t_shell *shell, t_command *cmd)
{
	char	*path;

	path = NULL;
	if (!cmd || !cmd->args)
		return (NULL);
	else if (cmd->args[1] == NULL)
		path = redir_cd_no_arg(shell);
	else if (cmd->args[1][0] == '~')
		path = redir_cd_tilde(shell, cmd);
	else if (ft_strcmp(cmd->args[1], "-") == 0)
		path = redir_cd_dash(shell);
	else
		path = ft_strdup(cmd->args[1]);
	return (path);
}
