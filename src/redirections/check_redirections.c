/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 14:05:39 by aledos-           #+#    #+#             */
/*   Updated: 2025/03/28 15:02:42 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// =============================================================================
// redir_input :
//
// permet de gerer le cas '<'
// exemple : cat < file, affiche le contenu de file
//
// =============================================================================
// redir_output :
//
// permet de gerer le cas '>'
// exemple : echo bonjour > out
// creer un fichier out et ecris l arg bonjour
// si le fichier exite deja le contenu est remplacer
//
// =============================================================================
// redir_append :
//
// permet de gerer le cas '>>'
// exemple : echo salut >> out
// contenu de out avec echo bonjour > out = bonjour
// echo salut >> out
// contenu de out -> bonjour
//					 salut
// si le fichier existe le contenu n est pas supprimer mais ajouter a la suite
//
// =============================================================================
// redir_heredoc :
//
// permet de gere le cas <<
// exemple : cat << end
// ouvre readline '>'
// permet d'ecrire du texte
// si end est entree, on quitte heredoc
//
// =============================================================================

int	redir_input(t_command *cmd)
{
	int	fd;

	if (cmd->input)
	{
		fd = open(cmd->input, O_RDONLY);
		if (fd == -1)
		{
			print_error(cmd->input);
			return (1);
		}
		if (dup2(fd, STDIN_FILENO) == -1)
		{
			perror("dup2 input");
			close(fd);
			return (1);
		}
		close(fd);
	}
	return (0);
}

int	redir_output(t_command *cmd)
{
	int	fd;

	if (cmd->output)
	{
		fd = open(cmd->output, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
		{
			print_error(cmd->output);
			return (1);
		}
		if (dup2(fd, STDOUT_FILENO) == -1)
		{
			perror("dup2 output");
			close(fd);
			return (1);
		}
		close(fd);
	}
	return (0);
}

int	redir_append(t_command *cmd)
{
	int	fd;

	if (cmd->append)
	{
		fd = open(cmd->append, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd == -1)
		{
			print_error(cmd->append);
			return (1);
		}
		if (dup2(fd, STDOUT_FILENO) == -1)
		{
			perror("dup2 output");
			close(fd);
			return (1);
		}
		close(fd);
	}
	return (0);
}

int	read_heredoc(t_command *cmd, char *line, int heredoc_fd[2])
{
	if (line == NULL || ft_strcmp(line, cmd->heredoc) == 0)
	{
		free(line);
		return (0);
	}
	write(heredoc_fd[1], line, ft_strlen(line));
	write(heredoc_fd[1], "\n", 1);
	free(line);
	return (1);
}

int	redir_heredoc(t_command *cmd)
{
	int		heredoc_fd[2];
	char	*line;

	if (pipe(heredoc_fd) == -1)
	{
		perror("pipe");
		return (1);
	}
	while (1)
	{
		line = readline("> ");
		if (read_heredoc(cmd, line, heredoc_fd) != 1)
			break ;
	}
	close(heredoc_fd[1]);
	if (dup2(heredoc_fd[0], STDIN_FILENO) == -1)
	{
		perror("dup2");
		close(heredoc_fd[0]);
		return (1);
	}
	close(heredoc_fd[0]);
	return (0);
}
