/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: casimarasn <casimarasn@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 20:14:57 by msedeno-          #+#    #+#             */
/*   Updated: 2026/01/25 20:26:47 by casimarasn       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* --- Standard Libraries --- */
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <signal.h>
# include <string.h> // <--- NUEVO: Para strerror
# include <errno.h>  // <--- NUEVO: Para errno
# include <readline/readline.h>
# include <readline/history.h>

/* --- Project Libraries --- */
# include "../src/my_lib/includes/libft.h"

/* --- Module Headers --- */
# include "utils.h"
# include "lexer.h"
# include "parser.h"
# include "executer.h"
# include "expander.h"
# include "builtins.h"

/* ************************************************************************** */
/*                              ANSI COLORS                                   */
/* ************************************************************************** */

# define RED "\033[38;5;196m"
# define ORANGE "\033[38;5;208m"
# define YELLOW "\033[38;5;226m"
# define GREEN "\033[38;5;46m"
# define BLUE "\033[38;5;21m"
# define PURPLE "\033[38;5;129m"
# define NC "\033[0m"

/* ************************************************************************** */
/*                            GLOBAL VARIABLE                                 */
/* ************************************************************************** */

/**
 * @brief Global exit status variable.
 * Stores the exit code of the last executed command or signal.
 * 
 * Defined as volatile sig_atomic_t to be safely modified inside signal handlers.
 * - 0:  Success
 * - 1:  General error
 * - 127: Command not found
 * - 130: Terminated by Ctrl+C (SIGINT)
 * - 131: Terminated by Ctrl+\ (SIGQUIT)
 */
extern volatile sig_atomic_t	g_exit_status;

/* ************************************************************************** */
/*                            SIGNAL HANDLING                                 */
/* ************************************************************************** */

/**
 * @brief Sets up signal handlers for the interactive shell mode.
 * 
 * Typical behavior:
 * - SIGINT (Ctrl+C): Displays a new prompt on a new line.
 * - SIGQUIT (Ctrl+\): Ignored (does nothing).
 */
void	setup_signals_interactive(void);

/**
 * @brief Sets up signal handlers for the child execution mode.
 * 
 * Typical behavior during blocking commands (e.g., inside 'cat'):
 * - Signals should perform their default action or forward to child.
 * - Allows the child process to be killed by Ctrl+C/Ctrl+\.
 */
void	setup_signals_execution(void);

#endif