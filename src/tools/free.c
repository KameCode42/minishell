/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dle-fur <dle-fur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 02:00:22 by aledos-           #+#    #+#             */
/*   Updated: 2025/04/04 12:36:06 by dle-fur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// =============================================================================
// cleanup_command :
//
// Libère toute la mémoire associée aux commandes et tokens courants du shell.
//
// @param shell: structure shell principale
// @note: Réinitialise à NULL les pointeurs libérés pour éviter les double free
//
// =============================================================================
// cleanup_shell :
//
// Libère toute la mémoire allouée pour la structure shell avant la sortie.
// Nettoie l'environnement, l'entrée, les tokens et les commandes.
//
// @param shell: structure shell principale à nettoyer
// @note: Efface également l'historique readline et réinitialise la structure
//        avec ft_memset pour éviter tout comportement indéfini
//
// =============================================================================

void	*free_env_list(t_env *env)
{
	t_env	*current;
	t_env	*next;

	current = env;
	while (current)
	{
		next = current->next;
		free(current->name);
		free(current->value);
		free(current);
		current = next;
	}
	return (NULL);
}

void	free_tokens(t_token *token)
{
	t_token	*current;
	t_token	*next;

	if (!token)
		return ;
	current = token;
	while (current)
	{
		next = current->next;
		free_token(current);
		current = next;
	}
}

void	free_commands(t_command *cmd)
{
	t_command	*current;
	t_command	*next;

	if (!cmd)
		return ;
	current = cmd;
	while (current)
	{
		next = current->next;
		free_command(current);
		current = next;
	}
}

void	cleanup_command(t_shell *shell)
{
	if (!shell)
		return ;
	if (shell->input)
	{
		free(shell->input);
		shell->input = NULL;
	}
	if (shell->tokens)
	{
		free_tokens(shell->tokens);
		shell->tokens = NULL;
	}
	if (shell->cmds)
	{
		free_commands(shell->cmds);
		shell->cmds = NULL;
	}
}

void	cleanup_shell(t_shell *shell)
{
	if (shell->env)
		free_env(shell);
	if (shell->input)
		free(shell->input);
	if (shell->tokens)
		free_tokens(shell->tokens);
	if (shell->cmds)
		free_commands(shell->cmds);
	ft_memset(shell, 0, sizeof(t_shell));
	rl_clear_history();
}
