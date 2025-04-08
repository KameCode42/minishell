/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dle-fur <dle-fur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 01:33:25 by aledos-           #+#    #+#             */
/*   Updated: 2025/04/04 09:34:10 by dle-fur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_shell(t_shell *shell, char **envp)
{
	ft_memset(shell, 0, sizeof(t_shell));
	shell->env = init_env(envp);
	shell->prev_fd = -1;
	shell->running = 1;
	setup_signals();
}

int	read_input(t_shell *shell)
{
	char	*input;

	shell->input = readline("minishell$ ");
	if (!shell->input)
	{
		rl_on_new_line();
		rl_replace_line("exit", 0);
		rl_redisplay();
		ft_putchar_fd('\n', 1);
		shell->running = 0;
		return (0);
	}
	input = shell->input;
	while (*input && ft_isspace(*input))
		input++;
	if (*input != '\0')
	{
		add_history(shell->input);
		return (1);
	}
	free(shell->input);
	shell->input = NULL;
	return (-1);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell		shell;
	int			input;

	(void)argc;
	(void)argv;
	init_shell(&shell, envp);
	while (shell.running)
	{
		input = read_input(&shell);
		if (input == 1)
		{
			if (parse_input(&shell) == 0)
			{
				shell.exit_status = 0;
				execute_commands(&shell);
			}
			cleanup_command(&shell);
		}
	}
	cleanup_shell(&shell);
	return (shell.exit_status);
}
