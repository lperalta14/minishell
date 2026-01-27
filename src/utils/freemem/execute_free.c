#include "../../../include/minishell.h"

void	clean_child_exit(int status, t_env **env, char *path, char **mat, t_command *cmds)
{
	if (path)
		free(path);
	if (mat)
		ft_freematrix(mat);
	if (cmds)
		free_commands(cmds);
	free_env_list(*env);
	rl_clear_history();
	exit(status);
}
