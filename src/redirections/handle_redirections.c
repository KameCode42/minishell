/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dle-fur <dle-fur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 14:06:17 by aledos-           #+#    #+#             */
/*   Updated: 2025/04/04 11:50:05 by dle-fur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error(const char *file)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd((char *)file, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd("\n", 2);
}

int	handle_redirections(t_command *cmd)
{
	if (!cmd)
		return (0);
	if (cmd->heredoc)
	{
		if (redir_heredoc(cmd) != 0)
			return (1);
	}
	else if (cmd->input)
	{
		if (redir_input(cmd) != 0)
			return (1);
	}
	if (cmd->append)
	{
		if (redir_append(cmd) != 0)
			return (1);
	}
	else if (cmd->output)
	{
		if (redir_output(cmd) != 0)
			return (1);
	}
	return (0);
}
