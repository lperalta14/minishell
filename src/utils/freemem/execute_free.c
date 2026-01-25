#include "../../../include/minishell.h"

void	clean_child_exit(int status, t_env **env, char *path, char **mat)
{
	if (path)
		free(path);
	if (mat)
		ft_freematrix(mat);
	free_env_list(*env);
	rl_clear_history();
	exit(status);
}
