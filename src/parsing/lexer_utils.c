/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aledos-s <aledos-s@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 14:07:42 by aledos-           #+#    #+#             */
/*   Updated: 2025/03/04 16:02:51 by aledos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_space(int c)
{
	if (c == 32 || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

int	is_operator(int c)
{
	if (c == '<' || c == '>' || c == '|' || c == '&'
		|| c == '(' || c == ')' || c == '*')
		return (1);
	return (0);
}

int	is_quote(int c)
{
	if (c == '\'' || c == '\"')
		return (1);
	return (0);
}

int	has_quote(char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
	{
		if (is_quote(s[i]))
			return (1);
		i++;
	}
	return (0);
}

int	has_variable(char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
	{
		if (s[i] == '$' && s[i + 1] && ((s[i + 1] == '?')
				|| ((s[i + 1]) >= 'A' && s[i + 1] <= 'Z')
				|| ((s[i + 1]) >= 'a' && s[i + 1] <= 'z')))
			return (1);
		i++;
	}
	return (0);
}
