#include "../../include/minishell.h"

static void	handle_redirs_only(t_command *cmd)
{
	pid_t	pid;
	int		status;

	if (cmd->redirs)
	{
		pid = fork();
		if (pid == 0)
		{
			if (check_redirs(cmd))
				exit(1);
			exit(0);
		}
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			g_exit_status = WEXITSTATUS(status);
	}
}

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

void	execute_simple_cmd(t_command *cmd, t_env **env)
{
	pid_t	pid;

	if (!cmd->args || cmd->args[0] == NULL)
	{
		handle_redirs_only(cmd);
		return ;
	}
	if (is_builtin(cmd->args[0]))
	{
		handle_builtin(cmd, env);
		return ;
	}
	pid = fork();
	if (pid == -1)
		return (perror("minishell: fork"));
	if (pid == 0)
		execute_child(cmd, env);
	else
		handle_parent_wait(pid);
}

void	execute_child(t_command *cmd, t_env **env)
{
	char		*path;
	char		**f_path;
	struct stat	st;

	if (check_redirs(cmd) != 0)
		exit(1);
	if (is_builtin(cmd->args[0]))
		exit(execute_builtin(cmd, env));
	path = get_path(cmd->args[0], *env);
	if (!path)
	{
		print_error(cmd->args[0], "command not found");
		exit(127);
	}
	if (stat(path, &st) == 0 && S_ISDIR(st.st_mode))
	{
		print_error(path, "Is a directory");
		exit(126);
	}
	f_path = env_to_array(*env);
	if (!f_path)
		exit(1);
	execve(path, cmd->args, f_path);
	print_error(cmd->args[0], strerror(errno));
	exit(126);
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