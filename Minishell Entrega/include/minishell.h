/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msedeno- <msedeno-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 20:14:57 by msedeno-          #+#    #+#             */
/*   Updated: 2026/01/23 17:12:08 by msedeno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <signal.h>
# include <string.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../src/my_lib/includes/libft.h"
# include "utils.h"
# include "lexer.h"
# include "parser.h"
# include "executer.h"
# include "expander.h"
# include "builtins.h"

# define RED "\033[38;5;196m"
# define ORANGE "\033[38;5;208m"
# define YELLOW "\033[38;5;226m"
# define GREEN "\033[38;5;46m"
# define BLUE "\033[38;5;21m"
# define PURPLE "\033[38;5;129m"
# define NC "\033[0m"

extern volatile sig_atomic_t	g_exit_status;
void	setup_signals_interactive(void);
void	setup_signals_execution(void);

#endif