/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aledos-s <aledos-s@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 16:04:13 by aledos-s          #+#    #+#             */
/*   Updated: 2025/03/04 16:10:20 by aledos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	copy_char(t_expand *exp, char *content)
{
	exp->result[exp->j] = content[exp->i];
	exp->j++;
	exp->i++;
}

void	add_to_result(t_expand *exp, char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		exp->result[exp->j] = s[i];
		exp->j++;
		i++;
	}
}

void	handle_single_quote(t_expand *exp, char *content)
{
	exp->result[exp->j] = content[exp->i];
	exp->j++;
	exp->i++;
	if (exp->in_s_quote == false)
		exp->in_s_quote = true;
	else
		exp->in_s_quote = false;
}

t_expand	*init_expansion(void)
{
	t_expand	*exp;

	exp = malloc(sizeof(t_expand));
	if (!exp)
		return (NULL);
	ft_memset(exp, 0, sizeof(t_expand));
	exp->result = malloc(sizeof(char) * PATH_MAX);
	if (!exp->result)
	{
		free(exp);
		return (NULL);
	}
	return (exp);
}
