/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 00:56:31 by aledos-           #+#    #+#             */
/*   Updated: 2025/03/30 14:13:11 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// =============================================================================
// init_commands :
//
// Initialise la structure de commandes dans la structure shell principale.
// Alloue la mémoire pour une nouvelle commande et l'initialise à zéro.
//
// @param shell: structure shell principale
// @return: 0 en cas de succès, 1 en cas d'erreur d'allocation
//
// =============================================================================

int	init_commands(t_shell *shell)
{
	t_command	*cmd;

	cmd = malloc(sizeof(t_command));
	if (!cmd)
		return (1);
	ft_memset(cmd, 0, sizeof(t_command));
	cmd->args = NULL;
	shell->cmds = cmd;
	return (0);
}

t_command	*create_command(void)
{
	t_command	*new;

	new = malloc(sizeof(t_command));
	if (!new)
		return (NULL);
	ft_memset(new, 0, sizeof(t_command));
	new->args = malloc(sizeof(char *));
	new->args[0] = NULL;
	return (new);
}

enum e_cmd_type	get_cmd_type(t_token *token)
{
	if (token->type == TOKEN_REDIR_IN)
		return (REDIR_IN);
	else if (token->type == TOKEN_REDIR_OUT)
		return (REDIR_OUT);
	else if (token->type == TOKEN_APPEND)
		return (APPEND);
	else if (token->type == TOKEN_HEREDOC)
		return (HEREDOC);
	return (COMMAND);
}

int	is_redirection(enum e_token_type type)
{
	if (type == TOKEN_REDIR_IN || type == TOKEN_REDIR_OUT
		|| type == TOKEN_APPEND || type == TOKEN_HEREDOC)
		return (1);
	return (0);
}

int	count_arguments(t_command *cmd)
{
	int	count;

	count = 0;
	if (cmd->args)
		while (cmd->args[count])
			count++;
	return (count);
}
