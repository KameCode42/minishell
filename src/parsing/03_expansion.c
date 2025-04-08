/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_expansion.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 01:05:38 by aledos-           #+#    #+#             */
/*   Updated: 2025/04/02 18:57:03 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// =============================================================================
// handle_special_var :
//
// Traite la variable spéciale $? qui contient le code de retour
// de la dernière commande exécutée.
//
// @param shell: structure shell contenant le statut de sortie
// @param exp: structure de contrôle de l'expansion
// @note: Convertit le code de retour en chaîne et l'ajoute au résultat
//
// =============================================================================
// get_env_var :
//
// Recherche une variable d'environnement dans la liste chaînée d'environnement.
//
// @param shell: structure shell contenant la liste d'environnement
// @param name: nom de la variable à rechercher
// @return: valeur de la variable ou NULL si non trouvée
//
// =============================================================================
// handle_env_var :
//
// Traite l'expansion d'une variable d'environnement standard.
//
// @param shell: structure shell contenant l'environnement
// @param exp: structure de contrôle de l'expansion
// @param content: contenu du token à analyser
// @param s: index de début du nom de la variable
// @note: Extrait le nom de la variable et ajoute sa valeur au résultat
//
// =============================================================================
// process_env_variable :
//
// Traite l'expansion des variables d'environnement dans le contenu d'un token.
//
// @param shell: structure shell contenant l'environnement
// @param exp: structure de contrôle de l'expansion
// @param content: contenu du token à analyser
// @note: Gère les cas spéciaux ($?, variables d'env, etc.)
//
// =============================================================================
// expand_variables :
//
// Fonction principale d'expansion des variables qui:
// - Analyse le contenu d'un token caractère par caractère
// - Gère les guillemets simples (pas d'expansion)
// - Remplace les variables par leurs valeurs
//
// @param shell: structure shell contenant l'environnement
// @param token: token dont le contenu doit être expansé
// @note: Modifie le contenu du token in-place
//
// =============================================================================

static void	handle_special_var(t_shell *shell, t_expand *exp)
{
	char	*var_value;

	var_value = ft_itoa(shell->exit_status);
	add_to_result(exp, var_value);
	free(var_value);
	exp->i++;
}

static char	*get_env_var(t_shell *shell, char *name)
{
	t_env	*env_list;

	env_list = shell->env;
	while (env_list)
	{
		if (ft_strcmp(env_list->name, name) == 0)
			return (env_list->value);
		env_list = env_list->next;
	}
	return (NULL);
}

static void	handle_env_var(t_shell *shell, t_expand *exp, char *content, int s)
{
	char	*var_name;
	char	*var_value;

	while (ft_isalnum(content[exp->i]) || content[exp->i] == '_')
		exp->i++;
	var_name = ft_substr(content, s, exp->i - s);
	var_value = get_env_var(shell, var_name);
	if (var_value)
		add_to_result(exp, var_value);
	free(var_name);
}

static void	process_env_variable(t_shell *shell, t_expand *exp, char *content)
{
	int	start;

	exp->i++;
	start = exp->i;
	if (content[exp->i] == '?')
	{
		handle_special_var(shell, exp);
		return ;
	}
	if (ft_isalpha(content[exp->i]) || content[exp->i] == '_')
		handle_env_var(shell, exp, content, start);
	else if (content[exp->i] == '\'' || content[exp->i] == '\"')
		exp->i = exp->i;
	else if (ft_isdigit(content[exp->i]))
		exp->i++;
	else
		exp->result[exp->j++] = '$';
}

void	expand_variables(t_shell *shell, t_token *token)
{
	t_expand	*exp;

	exp = init_expansion();
	if (!exp)
		return ;
	while (token->content[exp->i])
	{
		if (token->content[exp->i] == '\'')
			handle_single_quote(exp, token->content);
		else if (token->content[exp->i] == '$' && token->content[exp->i + 1]
			&& !exp->in_s_quote)
			process_env_variable(shell, exp, token->content);
		else
			copy_char(exp, token->content);
	}
	exp->result[exp->j] = '\0';
	free (token->content);
	token->content = exp->result;
	free(exp);
}
