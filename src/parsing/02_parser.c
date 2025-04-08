/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aledos-s <aledos-s@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 02:03:38 by aledos-           #+#    #+#             */
/*   Updated: 2025/03/17 08:39:35 by aledos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// =============================================================================
// remove_quotes :
//
// Supprime les guillemets d'un token tout en préservant le contenu entre
// guillemets. Gère les guillemets simples et doubles de manière appropriée.
//
// @param token: structure token contenant le contenu à nettoyer
// @note: Libère l'ancien contenu et alloue une nouvelle chaîne sans guillemets
//
// =============================================================================
// parse_tokens :
//
// Traite chaque token de la liste chaînée en effectuant:
// - L'expansion des variables d'environnement
// - La suppression des guillemets
//
// @param shell: structure shell contenant la liste des tokens
// @return: 0 en cas de succès, 1 en cas d'erreur
// @note: Modifie les tokens in-place
//
// =============================================================================

static void	remove_quotes(t_token *token)
{
	char	*new;
	int		i;
	int		j;
	bool	in_s_quote;
	bool	in_d_quote;

	new = malloc(sizeof(char) * (ft_strlen(token->content) + 1));
	i = 0;
	j = 0;
	in_s_quote = false;
	in_d_quote = false;
	while (token->content[i])
	{
		if (token->content[i] == '\'' && !in_d_quote)
			in_s_quote = !in_s_quote;
		else if (token->content[i] == '\"' && !in_s_quote)
			in_d_quote = !in_d_quote;
		else
			new[j++] = token->content[i];
		i++;
	}
	new[j] = '\0';
	free(token->content);
	token->content = new;
}

int	parse_tokens(t_shell *shell)
{
	t_token	*tkn;

	if (!shell || !shell->tokens)
		return (1);
	tkn = shell->tokens;
	while (tkn)
	{
		if (has_variable(tkn->content))
			expand_variables(shell, tkn);
		if (has_quote(tkn->content))
			remove_quotes(tkn);
		tkn = tkn->next;
	}
	return (0);
}
