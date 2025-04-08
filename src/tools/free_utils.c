/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 14:06:46 by aledos-           #+#    #+#             */
/*   Updated: 2025/04/03 18:22:49 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_array(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		arr[i] = NULL;
		i++;
	}
	free(arr);
}

void	free_token(t_token *token)
{
	if (!token)
		return ;
	free(token->content);
	free(token);
}

void	free_env(t_shell *shell)
{
	if (!shell || !shell->env)
		return ;
	shell->env = free_env_list(shell->env);
	shell->env = NULL;
}

void	free_env_array(char **env)
{
	free_array(env);
}

void	free_command(t_command *cmd)
{
	if (!cmd)
		return ;
	if (cmd->args)
		free_array(cmd->args);
	if (cmd->input)
		free(cmd->input);
	if (cmd->output)
		free(cmd->output);
	if (cmd->append)
		free(cmd->append);
	if (cmd->heredoc)
		free(cmd->heredoc);
	free(cmd);
}
