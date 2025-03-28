/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   05_commands_redir.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 14:04:04 by aledos-           #+#    #+#             */
/*   Updated: 2025/03/21 16:02:44 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// =============================================================================
// add_redir
// =============================================================================
//
// Gère les différents types de redirection pour une commande.
// Types supportés:
// - Redirection d'entrée (<)
// - Redirection de sortie (>)
// - Append (>>)
// - Heredoc (<<)
//
// Vérifie la validité du token suivant et met à jour la structure de commande
// avec les informations de redirection appropriées.
//
// @param cmd: structure de la commande à mettre à jour
// @param token: token de redirection actuel
// @param next: token suivant contenant le fichier/délimiteur
// @return: 0 en cas de succès, 1 en cas d'erreur
// =============================================================================

static int	handle_redir_in(t_command *cmd, t_token *token)
{
	if (cmd->input)
		free(cmd->input);
	cmd->input = ft_strdup(token->content);
	if (!cmd->input)
		return (1);
	return (0);
}

static int	handle_redir_out(t_command *cmd, t_token *token)
{
	int	fd;

	if (cmd->output)
		free(cmd->output);
	cmd->output = ft_strdup(token->content);
	if (!cmd->output)
		return (1);
	fd = open(cmd->output, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("minishell");
		return (1);
	}
	close(fd);
	return (0);
}

static int	handle_append(t_command *cmd, t_token *token)
{
	if (cmd->append)
		free(cmd->append);
	cmd->append = ft_strdup(token->content);
	if (!cmd->append)
		return (1);
	return (0);
}

static int	handle_heredoc(t_command *cmd, t_token *token)
{
	if (cmd->heredoc)
		free(cmd->heredoc);
	cmd->heredoc = ft_strdup(token->content);
	if (!cmd->heredoc)
		return (1);
	return (0);
}

int	add_redir(t_command *cmd, t_token *token, t_token *next)
{
	if (!next || next->type != TOKEN_WORD)
	{
		ft_putstr_fd(SYNTAX_ERR, 2);
		return (1);
	}
	if (token->type == TOKEN_REDIR_IN)
		return (handle_redir_in(cmd, next));
	else if (token->type == TOKEN_REDIR_OUT)
		return (handle_redir_out(cmd, next));
	else if (token->type == TOKEN_APPEND)
		return (handle_append(cmd, next));
	else if (token->type == TOKEN_HEREDOC)
		return (handle_heredoc(cmd, next));
	return (0);
}
