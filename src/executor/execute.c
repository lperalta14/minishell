#include "../../include/minishell.h"

void	execute_simple_cmd(t_command *cmd, t_env *env)
{
	pid_t	pid;
	char	*path;
	char	**f_path;

	if (!cmd-> args || cmd->args[0] == NULL)
		return ;
	pid = fork();
	if (pid == -1)
		return (perror("minishell: fork"));
	if ((pid == 0))
	{
		path = get_path(cmd->args[0], env);
		if (!path)
		{
			perror("minishell: command not found")
		}

	}

}