/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 14:29:53 by david             #+#    #+#             */
/*   Updated: 2025/03/14 21:42:23 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// =============================================================================
// remove_variable_env :
//
// supprime une variable d'environnement
// prev = garde une trace de l'element precedent
// parcour la liste, si la variable est trouve, on supprime
// si pas le premier élément, pointe element precedent sur le suivant
// si premier element de la liste, on met a jour la tete de la liste
// met à jour prev pour qu'il pointe sur l'élément courant (var1 -> var->3)
// current avance sur le prochain element de la liste
//
// =============================================================================
// execute_unset:
//
// parcour tous les arguments si -> unset HOME USER et supprime
//
// =============================================================================

void	remove_variable_env(t_shell *shell, char *var_name)
{
	t_env	*current;
	t_env	*prev;

	current = shell->env;
	prev = NULL;
	while (current != NULL)
	{
		if (ft_strcmp(current->name, var_name) == 0)
		{
			if (prev != NULL)
				prev->next = current->next;
			else
				shell->env = current->next;
			free(current->name);
			free(current->value);
			free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}

void	execute_unset(t_shell *shell, t_command *cmd)
{
	int	i;

	if (cmd->args[1] == NULL)
		return ;
	i = 1;
	while (cmd->args[i])
	{
		remove_variable_env(shell, cmd->args[i]);
		i++;
	}
}
