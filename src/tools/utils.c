/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 09:03:19 by david             #+#    #+#             */
/*   Updated: 2025/03/15 09:39:37 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_strnlen(const char *str, size_t max_len)
{
	size_t	len;

	len = 0;
	while (len < max_len && str[len] != '\0')
		len++;
	return (len);
}

char	*ft_strndup(const char *s1, size_t size)
{
	size_t	i;
	size_t	len;
	char	*dest;

	i = 0;
	len = ft_strnlen(s1, size);
	dest = malloc(len + 1);
	if (dest == NULL)
		return (NULL);
	while (i < len)
	{
		dest[i] = s1[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_getenv(t_shell *shell, char *name)
{
	t_env	*current;

	if (!shell || !name)
		return (NULL);
	current = shell->env;
	while (current)
	{
		if (ft_strcmp(current->name, name) == 0)
			return (ft_strdup(current->value));
		current = current->next;
	}
	return (NULL);
}

int	ft_isspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r')
		return (1);
	return (0);
}
