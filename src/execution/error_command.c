/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dle-fur <dle-fur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 19:34:50 by david             #+#    #+#             */
/*   Updated: 2025/04/04 11:30:13 by dle-fur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_cmd_not_found(t_command *cmd)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd->args[0], 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd("command not found\n", 2);
}

void	free_child(t_shell *shell, char **path)
{
	if (path != NULL)
		free_array(path);
	cleanup_command(shell);
	free_env_list(shell->env);
}
