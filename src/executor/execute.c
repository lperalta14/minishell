/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: casimarasn <casimarasn@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 20:14:06 by msedeno-          #+#    #+#             */
/*   Updated: 2026/01/23 16:30:39 by casimarasn       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	handle_parent_wait(pid_t pid)
{
	int	status;

	setup_signals_execution();
	waitpid(pid, &status, 0);
	setup_signals_interactive();
	if (WIFEXITED(status))
		g_exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		g_exit_status = 128 + WTERMSIG(status);
		if (WTERMSIG(status) == SIGINT)
			write(1, "\n", 1);
		else if (WTERMSIG(status) == SIGQUIT)
			ft_putendl_fd("Quit (core dumped)", 1);
	}
}

static void	handle_builtin(t_command *cmd, t_env **env)
{
	int	or_stdin;
	int	or_stdout;
	int	status;

	status = 0;
	or_stdin = dup(STDIN_FILENO);
	or_stdout = dup(STDOUT_FILENO);
	if (check_redirs(cmd) == 0)
		status = execute_builtin(cmd, env);
	dup2(or_stdin, STDIN_FILENO);
	dup2(or_stdout, STDOUT_FILENO);
	close(or_stdin);
	close(or_stdout);
	g_exit_status = status;
}

static void	handle_external(t_command *cmd, t_env **env, int stdin_bk)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (perror("minishell: fork"));
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		close(stdin_bk);
		execute_child(cmd, env);
	}
	else
		handle_parent_wait(pid);
}

void	execute_simple_cmd(t_command *cmd, t_env **env)
{
	int		std_in;

	std_in = dup(STDIN_FILENO);
	if (handle_heredocs_before_pipeline(cmd) != 0)
	{
		dup2(std_in, STDIN_FILENO); // Restaurar si se cancela con Ctrl+C
		close(std_in);
		return ;
	}
	if (!cmd->args || cmd->args[0] == NULL)
		handle_redirs_only(cmd);
	else if (is_builtin(cmd->args[0]))
		handle_builtin(cmd, env);
	else
		handle_external(cmd, env, std_in);
	dup2(std_in, STDIN_FILENO);
	close(std_in);
}

// 		/*
//               g_exit_status = 128 + WTERMSIG(status);
//             // AQUI ES DONDE VA EL NEWLINE:
//             // Si el hijo murió por SIGINT (Ctrl+C), imprimimos \n
//             if (WTERMSIG(status) == SIGINT)
//                 write(1, "\n", 1);
//             // Opcional: Para SIGQUIT (Ctrl+\) bash imprime esto:
//             else if (WTERMSIG(status) == SIGQUIT)
//                 ft_putendl_fd("Quit (core dumped)", 1);
// 		*/
// 	}