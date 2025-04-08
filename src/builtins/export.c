/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 15:46:04 by dle-fur           #+#    #+#             */
/*   Updated: 2025/03/21 15:25:59 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// =============================================================================
// execute_export
// =============================================================================
//
// permet d'exporter des variable, creer ou de modifier si deja existante
// si export = ou export 4USER=VALEUR, return erreur
// recherche du sign =, si trouver c'est une VAR
// extrait avant et apres = et stock dans char
// add_env_variable permet de rechercher, modifier ou creer une VAR=VALEUR
//
// =============================================================================

static int	is_valid_var_name(const char *name)
{
	int	i;

	if (!name || !name[0] || ft_isdigit(name[0]) || name[0] == '=')
		return (0);
	i = 0;
	while (name[i] && name[i] != '=')
	{
		if (!ft_isalnum(name[i]) && name[i] != '_' )
			return (0);
		i++;
	}
	return (1);
}

void	print_var_export(t_shell *shell)
{
	t_env	*current;

	current = shell->env;
	while (current != NULL)
	{
		printf("declare -x %s=\"%s\"\n", current->name, current->value);
		current = current->next;
	}
}

void	execute_export(t_shell *shell, t_command *cmd)
{
	char	*var_name;
	char	*var_value;
	char	*equal_sign;

	if (cmd->args[1] == NULL)
	{
		print_var_export(shell);
		return ;
	}
	if (!is_valid_var_name(cmd->args[1]))
	{
		ft_putstr_fd("minishell: export: '", 2);
		ft_putstr_fd(cmd->args[1], 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		shell->exit_status = 1;
		return ;
	}
	equal_sign = ft_strchr(cmd->args[1], '=');
	if (equal_sign == NULL)
		return ;
	var_name = ft_strndup(cmd->args[1], equal_sign - cmd->args[1]);
	var_value = ft_strdup(equal_sign + 1);
	add_env_variable(shell, var_name, var_value);
	free(var_name);
	free(var_value);
}
