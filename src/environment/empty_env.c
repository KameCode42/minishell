/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   empty_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aledos-s <aledos-s@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 12:41:37 by aledos-s          #+#    #+#             */
/*   Updated: 2025/03/17 16:47:22 by aledos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// =============================================================================
// create_env_node :
//
// Crée un nouveau nœud pour la liste des variables d'environnement.
// Alloue la mémoire nécessaire pour un nœud t_env et duplique le nom et
// la valeur fournis.
//
// @param name: Nom de la variable d'environnement à créer
// @param value: Valeur associée à la variable d'environnement
// @return: Le nouveau nœud créé ou NULL en cas d'échec d'allocation
//
// =============================================================================
// init_env :
//
// Initialise l'environnement du shell, soit en chargeant les variables
// d'environnement fournies, soit en créant un environnement minimal avec
// PWD, SHLVL et _ si aucun environnement n'est fourni.
//
// @param envp: Tableau des variables d'environnement du système
// @return: Pointeur vers la liste chaînée des variables d'environnement ou
//			NULL en cas d'échec
//
// =============================================================================

static t_env	*create_env_node(char *name, char *value)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->name = ft_strdup(name);
	new->value = ft_strdup(value);
	if (!new->name || !new->value)
	{
		free(new->name);
		free(new->value);
		free(new);
		return (NULL);
	}
	new->next = NULL;
	return (new);
}

t_env	*init_env(char **envp)
{
	t_env	*env;
	t_env	*tmp;
	char	cwd[PATH_MAX];

	if (!envp || !envp[0])
	{
		if (getcwd(cwd, PATH_MAX))
			env = create_env_node("PWD", cwd);
		else
			env = create_env_node("PWD", "/");
		if (!env)
			return (NULL);
		tmp = create_env_node("SHLVL", "1");
		if (!tmp)
			return (free_env_list(env), NULL);
		env->next = tmp;
		tmp->next = create_env_node("_", "/usr/bin/env");
		if (!tmp->next)
			return (free_env_list(env), NULL);
		return (env);
	}
	return (load_env(envp));
}
