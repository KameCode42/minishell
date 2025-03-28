/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 10:34:58 by david             #+#    #+#             */
/*   Updated: 2025/03/14 21:41:51 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// =============================================================================
// execute_env
// =============================================================================
//
// permet d'executer la commande env et d'afficher l'environnement de minishell
//
// =============================================================================

void	execute_env(t_shell *shell)
{
	t_env	*current;

	current = shell->env;
	while (current != NULL)
	{
		printf("%s=%s\n", current->name, current->value);
		current = current->next;
	}
}
