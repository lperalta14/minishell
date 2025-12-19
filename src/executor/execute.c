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
	(void)status; // Evitar warning de variable no usada por ahora
}

void	execute_simple_cmd(t_command *cmd, t_env **env)
{
	pid_t	pid;
	char	*path;
	char	**f_path;
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
		waitpid(pid, &status, 0);
		/*if (WIFEXITED(status))
			g_exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			g_exit_status = 128 + WTERMSIG(status);*/
	}
	// (Opcional) Aquí guardaremos el exit status en el futuro
	// if (WIFEXITED(status))
	// 		g_exit_status = WEXITSTATUS(status);
}

void	execute_child(t_command *cmd, t_env **env)
{
	pid_t	pid;
	char	*path;
	char	**f_path;
	int		status;

	if (check_redirs(cmd) != 0)
		exit(1);
	if (is_builtin(cmd) != 0)
	{
		execute_builtin(cmd, env);
		exit(status);
	}
	if ()
	{
		if (check_redirs(cmd) != 0)
			exit(1);
		path = get_path(cmd->args[0], *env);
		if (!path)
		{
			ft_putstr_fd("minishell: command not found: ", 2);
			ft_putendl_fd(cmd->args[0], 2);
			exit(127);
		}
		f_path = env_to_array(*env);
		if (!f_path)
			exit(1);
		execve(path, cmd->args, f_path);
		perror("execve");
		exit(126);
	}
}

int	check_redirs(t_command *cmd)
{
	t_redir	*tmp;
	int		fd;

	tmp = cmd->redirs;
	while (tmp)
	{
		fd = -1;
		if (tmp->type == REDIR_IN)
		{
			fd = open(tmp->file, O_RDONLY);
			if (fd < 0)
				return (perror("minishell: open input"), 1);
			dup2(fd, STDIN_FILENO);
		}
		else if (tmp->type == REDIR_OUT)
		{
			fd = open(tmp->file, O_WRONLY | O_TRUNC | O_CREAT, 0644);
			if (fd < 0)
				return (perror ("minishell: open output"), 1);
			dup2(fd, STDOUT_FILENO);
		}
		else if (tmp->type == REDIR_APPEND)
		{
			fd = open(tmp->file, O_WRONLY | O_APPEND | O_CREAT, 0644);
			if (fd < 0)
				return (perror ("minishell: open append"), 1);
			dup2(fd, STDOUT_FILENO);
		}
		if (fd != -1)
			close(fd);
		tmp = tmp->next;
	}
	return (0);
}
