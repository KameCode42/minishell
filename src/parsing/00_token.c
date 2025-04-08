/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_token.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dle-fur <dle-fur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 15:01:54 by aledos-           #+#    #+#             */
/*   Updated: 2025/04/04 12:43:36 by dle-fur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// =============================================================================
// handle_operator :
//
// Traite les opérateurs simples et doubles dans la chaîne d'entrée.
//
// @param shell: structure shell principale
// @param input: chaîne d'entrée à analyser
// @param start: position de début de l'opérateur
// @param i: position actuelle dans la chaîne
// @return: nouvelle position après le traitement ou -1 si erreur
//
// =============================================================================
// handle_quote :
//
// Traite un token entouré de guillemets (simples ou doubles).
//
// @param shell: structure shell principale
// @param input: chaîne d'entrée à analyser
// @param start: position de début du token
// @param i: position actuelle dans la chaîne
// @return: nouvelle position après le traitement ou -1 si erreur
//
// =============================================================================
// handle_word :
//
// Traite un token de type mot (sans guillemets ni opérateurs).
//
// @param shell: structure shell principale
// @param input: chaîne d'entrée à analyser
// @param start: position de début du token
// @param i: position actuelle dans la chaîne
// @return: nouvelle position après le traitement ou -1 si erreur
//
// =============================================================================
// tokenize_input :
//
// Fonction principale de tokenization qui:
// - Découpe l'entrée en tokens distincts
// - Gère les opérateurs, guillemets et mots
// - Crée la liste chaînée de tokens
//
// @param shell: structure shell contenant l'entrée à tokenizer
// @return: 0 en cas de succès, 1 en cas d'erreur
// @note: Les tokens sont stockés dans shell->tokens
//
// =============================================================================
// parse_input :
//
// Fonction principale d'analyse syntaxique qui:
// 1. Tokenize l'entrée utilisateur
// 2. Traite les tokens (variables et guillemets)
// 3. Crée les structures de commandes
//
// @param shell: structure shell principale
// @return: 0 en cas de succès, 1 en cas d'erreur
// @note: Exécute les étapes de parsing séquentiellement
//
// =============================================================================

static int	handle_operator(t_shell *shell, char *input, int start, int i)
{
	if ((input[start] == '<' && input[start + 1] == '<')
		|| (input[start] == '>' && input[start + 1] == '>'))
	{
		if (add_token(shell, input, start, start + 2) != 0)
			return (-1);
		return (i + 2);
	}
	else
	{
		if (add_token(shell, input, start, start + 1) != 0)
			return (-1);
		return (i + 1);
	}
}

static int	handle_quote(t_shell *shell, char *input, int start, int i)
{
	char	quote;

	quote = input[i];
	i++;
	while (input[i] && input[i] != quote)
		i++;
	if (!input[i])
	{
		shell->exit_status = 2;
		return (ft_putendl_fd("minishell: syntax error unclosed quote", 2), -1);
	}
	i++;
	if (i - start == 2)
	{
		if (add_token(shell, input, start, i) != 0)
			return (-1);
		return (i);
	}
	while (input[i] && !is_space(input[i]) && !is_operator(input[i]))
		i++;
	if (add_token(shell, input, start, i) != 0)
		return (-1);
	return (i);
}

static int	handle_word(t_shell *shell, char *input, int start, int i)
{
	while (input[i] && !is_space(input[i]) && !is_operator(input[i]))
		i++;
	if (add_token(shell, input, start, i) != 0)
		return (-1);
	return (i);
}

static int	tokenize_input(t_shell *shell)
{
	int		i;
	int		token_start;
	char	*input;

	if (!shell || !shell->input || !shell->input[0])
		return (1);
	input = shell->input;
	i = 0;
	while (input[i])
	{
		while (input[i] && is_space(input[i]))
			i++;
		if (!input[i])
			break ;
		token_start = i;
		if (is_operator(input[i]))
			i = handle_operator(shell, input, token_start, i);
		else if (is_quote(input[i]))
			i = handle_quote(shell, input, token_start, i);
		else
			i = handle_word(shell, input, token_start, i);
		if (i == -1)
			return (1);
	}
	return (0);
}

int	parse_input(t_shell *shell)
{
	if (tokenize_input(shell) != 0)
	{
		free_tokens(shell->tokens);
		shell->tokens = NULL;
		return (1);
	}
	if (valid_tokens(shell) != 0)
	{
		free_tokens(shell->tokens);
		shell->tokens = NULL;
		return (1);
	}
	if (parse_tokens(shell) != 0)
	{
		free_tokens(shell->tokens);
		shell->tokens = NULL;
		return (1);
	}
	if (build_commands(shell) != 0)
	{
		cleanup_command(shell);
		return (1);
	}
	return (0);
}
