/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 11:28:27 by aledos-           #+#    #+#             */
/*   Updated: 2025/03/21 15:25:51 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// =============================================================================
// check_valid_exit :
//
// si premiere caractere est un signe, on avance d un char
// si rien apres le signe, return erreur
// verifie sans signe et apres signe si autre que des chiffre sont present
// si oui return erreur
//
// =============================================================================
// execute_exit:
//
// si args = exit, exit normalement
// si exit = exit 1 2, return erreur
// check si args->exit = valid, si ok
// convertir la str de sortie en int
// free l environnement
// cast pour etre entre 0 et 255
//
//=============================================================================

void	print_exit_error(t_shell *shell, char *args)
{
	ft_putstr_fd("exit\n", 1);
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(args, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	cleanup_shell(shell);
	exit(2);
}

void	check_valid_exit(t_shell *shell, t_command *cmd)
{
	int	i;

	i = 0;
	if (cmd->args[1][0] == '-' || cmd->args[1][0] == '+')
		i = 1;
	if (cmd->args[1][i] == '\0')
		print_exit_error(shell, cmd->args[1]);
	while (cmd->args[1][i] != '\0')
	{
		if (!ft_isdigit(cmd->args[1][i]))
			print_exit_error(shell, cmd->args[1]);
		i++;
	}
}

void	execute_exit(t_shell *shell, t_command *cmd)
{
	int	exit_code;

	exit_code = 0;
	if (cmd->args[1] == NULL)
	{
		ft_putstr_fd("exit\n", 1);
		cleanup_shell(shell);
		exit (0);
	}
	check_valid_exit(shell, cmd);
	if (cmd->args[2])
	{
		ft_putstr_fd("exit\n", 1);
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		shell->exit_status = 1;
		return ;
	}
	ft_putstr_fd("exit\n", 1);
	exit_code = ft_atoi(cmd->args[1]);
	cleanup_shell(shell);
	exit((unsigned char)exit_code);
}
