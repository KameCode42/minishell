/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 12:54:01 by david             #+#    #+#             */
/*   Updated: 2025/04/03 14:11:32 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	wait_for_children(t_shell *shell)
{
	int		status;
	pid_t	pid;

	pid = waitpid(-1, &status, 0);
	while (pid > 0)
	{
		handle_child_exit_status(shell, status);
		pid = waitpid(-1, &status, 0);
	}
}

void	error_fork(void)
{
	perror("fork");
	exit(1);
}

void	error_dup2(int fd_1, int fd_2, const char *msg)
{
	if (fd_1 != -1)
		close(fd_1);
	if (fd_2 != -1)
		close(fd_2);
	perror(msg);
	exit (1);
}

int	create_pipe(int pipe_fd[2])
{
	if (pipe(pipe_fd) == -1)
	{
		perror("Error creating pipe");
		return (1);
	}
	return (0);
}
