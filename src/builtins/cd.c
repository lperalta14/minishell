#include "../../include/minishell.h"

static char	*get_env_value(t_env *env, char *key)
{
	t_env	*aux;

	aux = find_env(env, key);
	if (aux)
		return (aux->value);
	else
		return (NULL);
}

static void	update_wds(t_env *env)
{
	t_env	*pwd;
	t_env	*old;

	pwd = find_env(env, "PWD");
	old = find_env(env, "OLDPWD");
	if (old && pwd && pwd->value)
	{
		free(old->value);
		old->value = ft_strdup(pwd->value);
	}
	if (pwd)
	{
		free(pwd->value);
		pwd->value = getcwd(NULL, 0);
	}
}

int	ft_cd(t_command *cmd, t_env *env)
{
	char	*dest;

	if (!cmd->args[1])
	{
		dest = get_env_value(env, "HOME");
		if (!dest)
		{
			ft_putendl_fd("minishell: HOME not set", 2);
			return (1);
		}
	}
	else if (ft_strncmp(cmd->args[1], "-", 2) == 0)
	{
		dest = get_env_value(env, "OLDPWD");
		if (!dest)
		{
			ft_putendl_fd("minishell: OLDPWD not set", 2);
			return (1);
		}
		ft_putendl_fd(dest, 1);
	}
	else
		dest = cmd->args[1];
	if (chdir(dest) == -1)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(dest, 2);
		ft_putendl_fd(": No such file or directory", 2);	
		return (1);
	}
	update_wds(env);
	return (0);
}
