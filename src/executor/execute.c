#include "../../include/minishell.h"

//restaura la entrada y salda de los fd originales para el proceso padre.
static void	restore_fds(int or_stdin, int or_stdout)
{
	dup2(or_stdin, STDIN_FILENO);
	dup2(or_stdout, STDOUT_FILENO);
	close(or_stdin);
	close(or_stdout);
}

static void	handle_builtin(t_command *cmd, t_env **env)
{
	int	or_stdin;
	int	or_stdout;
	int	status;

	or_stdin = dup(STDIN_FILENO);
	or_stdout = dup(STDOUT_FILENO);
	if (check_redirs(cmd) == 0)
		status = execute_builtin(cmd, env);
	restore_fds(or_stdin, or_stdout);
	(void)status;
}

void	execute_simple_cmd(t_command *cmd, t_env **env)
{
	pid_t	pid;
	int		status;

	if (!cmd-> args || cmd->args[0] == NULL)
		return ;
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
	{
		setup_signals_execution();
		waitpid(pid, &status, 0);
		setup_signals_interactive();
		if (WIFEXITED(status))
			g_exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			g_exit_status = 128 + WTERMSIG(status);
		/*
              g_exit_status = 128 + WTERMSIG(status);
            
            // AQUI ES DONDE VA EL NEWLINE:
            // Si el hijo murió por SIGINT (Ctrl+C), imprimimos \n
            if (WTERMSIG(status) == SIGINT)
                write(1, "\n", 1);
            
            // Opcional: Para SIGQUIT (Ctrl+\) bash imprime esto:
            else if (WTERMSIG(status) == SIGQUIT)
                ft_putendl_fd("Quit (core dumped)", 1);
		*/
	}
}

void	execute_child(t_command *cmd, t_env **env)
{
	char	*path;
	char	**f_path;
	int		status;

	if (check_redirs(cmd) != 0)
		exit(1);
	if (is_builtin(cmd->args[0]))
	{
		status = execute_builtin(cmd, env);
		exit(status);
	}
	path = get_path(cmd->args[0], *env);
	if (!path)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd->args[0], 2);
		ft_putendl_fd(": command not found", 2);
		exit(127);
	}
	f_path = env_to_array(*env);
	if (!f_path)
		exit(1);
	execve(path, cmd->args, f_path);
	perror("minishell: execve");
	exit(126);
}
