/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 16:22:39 by david             #+#    #+#             */
/*   Updated: 2025/03/21 15:26:28 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// =============================================================================
// copy_env :
//
// permet de copier envp de bash dans la structure shell->env_list de minishell
// cherche le sign = dans la liste
// init d'un new temporaire
// extrait le nom avant =, et extrait la valeur apres =
// init le premier element avec head (HOME=....)
// chaque nouvel element sera ranger dans tail afin d'etre afficher a la suite
//
// =============================================================================
// load_env :
//
// permet de stocker envp dans shell->env_list
// parcours envp, copier chaque element avec copy_env
// head = premier element de la liste
// tail = element suivant
// shell->env_list permet d’accéder à toute la liste
//
// =============================================================================
// find_env_var :
//
// recherche une variable d'environnement dans la liste chaînée env_list
// on compare le name (HOME), si existe on passe au next
// retourne NULL si existe pas
//
//=============================================================================
// add_env_variable :
//
// ajoute une nouvelle variable d'environnement si elle n'existe pas
// si la value existe on la remplace simplement et la met a jour
// sinon on cree un nouveau noeud, on dup le name et la value
// on stocke dans shell->env_list
//
// =============================================================================
// update_pwd_env :
//
// gère la mise à jour des variables d'environnement OLDPWD et PWD après un cd
// avec add_env_variable on change le repertoire a chaque cd - et met a jour
//
// =============================================================================

void	copy_env(char *envp, t_env **head, t_env **tail)
{
	t_env	*new;
	char	*equal_sign;

	equal_sign = ft_strchr(envp, '=');
	if (equal_sign == NULL)
		return ;
	if (equal_sign)
	{
		new = malloc(sizeof(t_env));
		if (new == NULL)
			return ;
		new->name = ft_strndup(envp, equal_sign - envp);
		new->value = ft_strdup(equal_sign + 1);
		new->next = NULL;
		if (*head == NULL)
			*head = new;
		else
			(*tail)->next = new;
		*tail = new;
	}
}

t_env	*load_env(char **envp)
{
	t_env	*head;
	t_env	*tail;
	int		i;

	head = NULL;
	tail = NULL;
	i = 0;
	while (envp[i] != NULL)
	{
		copy_env(envp[i], &head, &tail);
		i++;
	}
	return (head);
}

t_env	*find_env_var(t_shell *shell, char *var_name)
{
	t_env	*env;

	env = shell->env;
	while (env != NULL)
	{
		if (ft_strcmp(env->name, var_name) == 0)
			return (env);
		env = env->next;
	}
	return (NULL);
}

void	add_env_variable(t_shell *shell, char *name, char *value)
{
	t_env	*env;
	t_env	*new;

	env = find_env_var(shell, name);
	if (env)
	{
		free(env->value);
		env->value = ft_strdup(value);
	}
	else
	{
		new = malloc(sizeof(t_env));
		if (new == NULL)
			return ;
		new->name = ft_strdup(name);
		new->value = ft_strdup(value);
		new->next = shell->env;
		shell->env = new;
	}
}

void	update_pwd_env(t_shell *shell, char *old_pwd)
{
	char	*new_pwd;

	new_pwd = getcwd(NULL, 0);
	if (new_pwd == NULL)
	{
		perror("minishell: cd");
		return ;
	}
	add_env_variable(shell, "OLDPWD", old_pwd);
	add_env_variable(shell, "PWD", new_pwd);
	free(new_pwd);
}
