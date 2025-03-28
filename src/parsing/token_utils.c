/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aledos- <42lausanne>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 15:03:17 by aledos-           #+#    #+#             */
/*   Updated: 2025/03/20 15:03:30 by aledos-          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	add_token(t_shell *shell, char *input, int start, int i)
{
	t_token				*new;
	t_token				*last;
	char				*content;
	enum e_token_type	type;

	content = ft_substr(input, start, i - start);
	if (!content)
		return (1);
	type = get_token_type(content);
	new = create_token(content, type);
	free(content);
	if (!new)
		return (1);
	if (!shell->tokens)
		shell->tokens = new;
	else
	{
		last = shell->tokens;
		while (last->next != NULL)
			last = last->next;
		last->next = new;
	}
	return (0);
}

t_token	*create_token(char *content, enum e_token_type type)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->content = ft_strdup(content);
	new->type = type;
	new->next = NULL;
	return (new);
}

enum e_token_type	get_token_type(char *content)
{
	if (ft_strncmp(content, "|", 1) == 0)
		return (TOKEN_PIPE);
	else if (ft_strncmp(content, "<<", 2) == 0)
		return (TOKEN_HEREDOC);
	else if (ft_strncmp(content, "<", 1) == 0)
		return (TOKEN_REDIR_IN);
	else if (ft_strncmp(content, ">>", 2) == 0)
		return (TOKEN_APPEND);
	else if (ft_strncmp(content, ">", 1) == 0)
		return (TOKEN_REDIR_OUT);
	return (TOKEN_WORD);
}

int	count_tokens(t_token *tokens)
{
	t_token	*current;
	int		count;

	count = 0;
	current = tokens;
	while (current)
	{
		current = current->next;
		count++;
	}
	return (count);
}

t_token	*get_token_by_index(t_token *token, int index)
{
	t_token	*current;
	int		i;

	i = 0;
	current = token;
	while (current && i < index)
	{
		current = current->next;
		i++;
	}
	return (current);
}
