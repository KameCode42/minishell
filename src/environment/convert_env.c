/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 12:14:51 by david             #+#    #+#             */
/*   Updated: 2025/04/03 13:24:45 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// =============================================================================
// env_list_size :
//
// permet de compter le nombre de ligne que contient l'env
//
// =============================================================================
// malloc_env_list :
//
// permet d'allouer la ligne de l'env
// copie le nom dans str -> HOME
// copie le = apres le nom -> HOME=
// copie la valeur apres le = -> HOME=user.....
//
// =============================================================================
// convert_env_list:
//
// permet de convertir l'env en tableau (utiliser pour execve)
// malloc la taille du tableau
// parcour l'env avec un tmp
// alloue la taille pour la ligne
// return le tableau
//
//=============================================================================

int	env_list_size(t_shell *shell)
{
	t_env	*env_tmp;
	int		count;

	count = 0;
	env_tmp = shell->env;
	while (env_tmp != NULL)
	{
		count++;
		env_tmp = env_tmp->next;
	}
	return (count);
}

char	*malloc_env_list(t_env *env)
{
	char	*str;
	int		len;

	len = ft_strlen(env->name) + ft_strlen(env->value) + 2;
	str = malloc(sizeof(char) * len);
	if (str == NULL)
		return (NULL);
	ft_strcpy(str, env->name);
	ft_strcpy(str + ft_strlen(env->name), "=");
	ft_strcpy(str + ft_strlen(env->name) + 1, env->value);
	return (str);
}

char	**convert_env_list(t_shell *shell)
{
	int		i;
	char	**tab_env;
	t_env	*env_tmp;

	tab_env = malloc(sizeof(char *) * (env_list_size(shell) + 1));
	if (tab_env == NULL)
		return (NULL);
	env_tmp = shell->env;
	i = 0;
	while (env_tmp != NULL)
	{
		tab_env[i] = malloc_env_list(env_tmp);
		if (tab_env[i] == NULL)
		{
			free_env_array(tab_env);
			return (NULL);
		}
		env_tmp = env_tmp->next;
		i++;
	}
	tab_env[i] = NULL;
	return (tab_env);
}
