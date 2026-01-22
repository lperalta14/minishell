/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msedeno- <msedeno-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 20:17:39 by msedeno-          #+#    #+#             */
/*   Updated: 2026/01/22 20:17:40 by msedeno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//Ctrl+C = SIGINT
void	handle_sigint_interactive(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_exit_status = 128 + SIGINT;
}

void	setup_signals_execution(void)
{
	struct sigaction	sa;

	sa.sa_handler = SIG_IGN; // El padre ignora la señal
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	// Ignoramos SIGINT (Ctrl+C) y SIGQUIT (Ctrl+\) en el padre
	// El hijo las recibirá por defecto y morirá
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}

void	setup_signals_interactive(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	// Configurar SIGINT (Ctrl+C)
	sa_int.sa_handler = handle_sigint_interactive;
	sa_int.sa_flags = SA_RESTART;
	sigemptyset(&sa_int.sa_mask);
	sigaction(SIGINT, &sa_int, NULL);

	// Ignorar SIGQUIT (Ctrl+\)
	sa_quit.sa_handler = SIG_IGN;
	sa_quit.sa_flags = 0;
	sigemptyset(&sa_quit.sa_mask);
	sigaction(SIGQUIT, &sa_quit, NULL);
}
