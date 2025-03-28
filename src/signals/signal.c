/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aledos-s <aledos-s@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 12:19:39 by aledos-           #+#    #+#             */
/*   Updated: 2025/03/18 14:11:37 by aledos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// =============================================================================
// g_signal_received :
//
// Variable globale stockant le numéro du dernier signal reçu par le shell.
// Déclarée comme volatile sig_atomic_t pour garantir des accès atomiques
// et éviter les optimisations du compilateur lors des accès concurrents.
// Utilisée comme unique point de communication entre le gestionnaire de
// signaux et le programme principal, conformément aux exigences du sujet.
//
// volatile sig_atomic_t	g_signal_received = 0;
//
// =============================================================================
// handle_signal :
//
// Gère les signaux reçus par le shell, notamment SIGINT (Ctrl-C).
// Affiche un nouveau prompt sur une nouvelle ligne lorsque Ctrl-C est pressé.
//
// @param sig_code: numéro du signal reçu
//
// =============================================================================
// setup_signals :
//
// Configure la gestion des signaux pour le shell.
// - SIGINT (Ctrl-C) : affiche un nouveau prompt
// - SIGQUIT (Ctrl-\) : ignoré complètement
//
// Utilise sigaction pour une gestion robuste des signaux.
//
// =============================================================================

volatile sig_atomic_t	g_signal_received = 0;

static void	handle_signal(int sig_code)
{
	if (sig_code == SIGINT)
	{
		g_signal_received = sig_code;
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	setup_signals(void)
{
	struct sigaction	sa;

	sa.sa_handler = handle_signal;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}

void	handle_child_exit_status(t_shell *shell, int status)
{
	if (WIFEXITED(status))
		shell->exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		shell->exit_status = 128 + WTERMSIG(status);
}
