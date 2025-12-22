#include "../../include/minishell.h"

void	execute_simple_cmd(t_command *cmd, t_env *env)
{
	pid_t	pid;
	char	*path;
	char	**f_path;
	int		status;

	if (!cmd-> args || cmd->args[0] == NULL)
		return ;
	if (is_builtin(cmd->args[0]))
	{
		status = execute_builtin(cmd, &env);
		return ;
	}
	pid = fork();
	if (pid == -1)
	{
		perror("minishell: fork");
		return ;
	}
	if (pid == 0)
	{
		path = get_path(cmd->args[0], env);
		if (!path)
		{
			ft_putstr_fd("minishell: command not found: ", 2);
			ft_putendl_fd(cmd->args[0], 2);
			exit(127);
		}
		f_path = env_to_array(env);
		if (!f_path)
			exit(1);
		execve(path, cmd->args, f_path);
		perror("execve");
		exit(126); // no ejecutable.
	}
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			g_exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			g_exit_status = 128 + WTERMSIG(status);
	}
	// (Opcional) Aquí guardaremos el exit status en el futuro
	// if (WIFEXITED(status))
	// 		g_exit_status = WEXITSTATUS(status);
}

void	check_redirs(t_command *cmd)
{
	t_command	*tmp;
	int			fd;

	tmp = cmd;
	fd = 0;
	while (tmp)
	{
		if (tmp->redirs->type == REDIR_IN)
		{
			fd = open(cmd->args[1], O_RDONLY); // open recibe el nombre del archivo(char *) y devuelve el fd. Amiga tremendo porro te has fumado 
			if (fd < 0)
			{
				perror ("open failure");
				exit (1);
			}
		}
	}
}
