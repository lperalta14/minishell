#include "../../include/minishell.h"

char	*find_valid_path(char *cmd, char **paths)
{
	int		i;
	char	*path_part;
	char	*full_path;

	i = 0;
	while (paths[i])
	{
		path_part = ft_strjoin(paths[i], "/");
		if (!path_part)
			return (NULL);
		full_path = ft_strjoin(path_part, cmd);
		free(path_part);
		if (!full_path)
			return (NULL);
		if (access(full_path, F_OK | X_OK) == 0)
			return (full_path);
		free(full_path);
		i++;
	}
	return (NULL);
}

char	*get_path(char *cmd, t_env *env)
{
	char	**paths;
	char	*final_path;

	if (ft_strchr(cmd, '/'))
		return (ft_strdup(cmd));
	while (env)
	{
		if (ft_strncmp(env->key, "PATH", 4) == 0)
			break ;
		env = env->next;
	}
	if (!env)
		return (NULL);
	paths = ft_split(env->value, ':');
	if (!paths)
		return (NULL);
	final_path = find_valid_path(cmd, paths);
	ft_freematrix(paths);
	return (final_path);
}
