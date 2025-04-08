/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_commands.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 01:28:28 by aledos-           #+#    #+#             */
/*   Updated: 2025/03/21 15:46:58 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// =============================================================================
// count_arguments :
//
// Compte le nombre d'arguments dans une commande.
// Parcourt le tableau d'arguments jusqu'à NULL.
//
// @param cmd: structure de la commande
// @return: nombre d'arguments dans la commande
//
// =============================================================================
// add_arguments :
//
// Ajoute un nouvel argument à la liste des arguments d'une commande.
//
// @param cmd: structure de la commande
// @param arg: argument à ajouter
// @return: 0 en cas de succès, 1 en cas d'erreur
//
// =============================================================================
// tokens_to_commands :
//
// Convertit une liste de tokens en commandes structurées.
// Gère les pipes, redirections et arguments.
//
// @param shell: structure shell principale
// @param token: liste des tokens à convertir
// @param cmd: commande à construire
// @return: 0 en cas de succès, 1 en cas d'erreur
//
// =============================================================================
// build_commands :
//
// Point d'entrée principal pour la construction des commandes.
// Initialise et construit la structure de commandes à partir des tokens.
//
// @param shell: structure shell principale
// @return: 0 en cas de succès, 1 en cas d'erreur
//
// =============================================================================

static int	free_and_return(char **arr, int i)
{
	while (i >= 0)
	{
		free(arr[i]);
		arr[i] = NULL;
		i--;
	}
	free(arr);
	return (1);
}

static int	add_arguments(t_command *cmd, char *arg)
{
	char	**new_arg;
	int		count;
	int		i;

	count = count_arguments(cmd);
	new_arg = malloc(sizeof(char *) * (count + 2));
	if (!new_arg)
		return (1);
	i = -1;
	while (++i < count)
	{
		new_arg[i] = ft_strdup(cmd->args[i]);
		if (!new_arg[i])
			return (free_and_return(new_arg, i));
	}
	new_arg[i] = ft_strdup(arg);
	if (!new_arg[i])
		return (free_and_return(new_arg, i));
	new_arg[i + 1] = NULL;
	if (cmd->args)
		free_array(cmd->args);
	cmd->args = new_arg;
	return (0);
}

static int	redirection(t_token **token, t_command *current)
{
	current->type = get_cmd_type(*token);
	if (add_redir(current, *token, (*token)->next))
		return (1);
	if ((*token)->next)
		*token = (*token)->next;
	else
		return (1);
	return (0);
}

static int	tokens_to_commands(t_token *token, t_command *cmd)
{
	t_command	*current;

	current = cmd;
	while (token)
	{
		if (token->type == TOKEN_PIPE)
		{
			current->type = PIPE;
			current->next = create_command();
			current = current->next;
		}
		else if (is_redirection(token->type))
		{
			if (redirection(&token, current))
				return (1);
		}
		else if (token->type == TOKEN_WORD)
		{
			if (add_arguments(current, token->content))
				return (1);
		}
		token = token->next;
	}
	return (0);
}

int	build_commands(t_shell *shell)
{
	if (init_commands(shell) != 0)
		return (1);
	if (tokens_to_commands(shell->tokens, shell->cmds) != 0)
		return (1);
	return (0);
}
