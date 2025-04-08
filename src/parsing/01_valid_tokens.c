/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_token.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 15:01:54 by aledos-           #+#    #+#             */
/*   Updated: 2025/03/21 15:27:00 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	error_syntax(t_shell *shell, char *content)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	ft_putstr_fd(content, 2);
	ft_putstr_fd("'\n", 2);
	shell->exit_status = 2;
	return (1);
}

static char	*get_content_error(t_token *token, t_token *next)
{
	(void)token;
	if (next)
		return (next->content);
	return ("newline");
}

static int	check_token(t_token *prev, t_token *next, int type)
{
	if (type == TOKEN_PIPE)
	{
		if (!prev)
			return (1);
		if (!next)
			return (1);
	}
	else if (type == TOKEN_REDIR_IN || type == TOKEN_REDIR_OUT
		|| type == TOKEN_APPEND || type == TOKEN_HEREDOC)
	{
		if (prev && !next)
			return (1);
	}
	return (0);
}

static int	check_syntax(t_shell *sh, t_token *p, t_token *token, t_token *next)
{
	char	*error;

	if (token->type != TOKEN_WORD)
	{
		if (check_token(p, next, token->type))
		{
			error = get_content_error(token, next);
			return (error_syntax(sh, error));
		}
	}
	return (0);
}

int	valid_tokens(t_shell *shell)
{
	t_token	*token;
	t_token	*prev;

	token = shell->tokens;
	prev = NULL;
	if (token && token->type == TOKEN_PIPE)
		return (error_syntax(shell, "|"));
	while (token)
	{
		if (check_syntax(shell, prev, token, token->next))
			return (1);
		prev = token;
		token = token->next;
	}
	return (0);
}
