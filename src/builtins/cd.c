#include "../../include/minishell.h"

char	*get_env_path(t_env *env, char *var, size_t len)
{
	t_env	*aux;

	aux = env;
	while (aux)
	{
		if (ft_strncmp(aux->key, var, len) == 0)
			return (aux->value);
		aux = aux->next;
	}
	return (NULL);
}

static void	update_env_var(t_env **env, char *key, char *value)
{
	t_env	*tmp;
	t_env	*n_node;
	char	*full_str;

	tmp = find_env(*env, key);
	if (tmp)
	{
		if (tmp->value)
			free(tmp->value);
		tmp->value = ft_strdup(value);
	}
	else
	{
		full_str = ft_strjoindelimit(key, "=", value);
		if (!full_str)
			return ;
		n_node = get_env_node(full_str);
		add_env(env, n_node);
		free(full_str);
	}
}

static char	*get_target_path(char **args, t_env *env)
{
	char	*path;

	if (!args[1])
	{
		path = get_env_path(env, "HOME", 5);
		if (!path)
			ft_putendl_fd("minishell: cd: HOME not set", 2);
	}
	else if (ft_strncmp(args[1], "-", 2) == 0)
	{
		path = get_env_path(env, "OLDPWD", 7);
		if (!path)
			ft_putendl_fd("minishell: cd: OLDPWD not set", 2);
		else
			ft_putendl_fd(path, 1);
	}
	else
		path = args[1];
	return (path);
}

/* static void	update_pwds(t_env **env, char *cur_dir) //char *args_path si chetada
{
	char	*n_dir;

	if (cur_dir)
	{
		update_env_var(env, "OLDPWD", cur_dir);
		free(cur_dir);
	}
	n_dir = getcwd(NULL, 0);
	if (n_dir)
	{
		update_env_var(env, "PWD", n_dir);
		free(n_dir);
	}
} */

static void	update_pwds(t_env **env, char *cur_dir, char *arg_path)
{
	char	*n_dir;
	char	*tmp_pwd;

	if (cur_dir)
	{
		update_env_var(env, "OLDPWD", cur_dir);
		free(cur_dir);
	}
	else // Si getcwd falló antes (carpborrada), intentamos usar el PWD del env
	{
		tmp_pwd = get_env_path(*env, "PWD", 3);
		if (tmp_pwd)
			update_env_var(env, "OLDPWD", tmp_pwd);
	}
	n_dir = getcwd(NULL, 0);
	if (n_dir)
	{
		update_env_var(env, "PWD", n_dir);
		free(n_dir);
	}
	else
	{ // 3. FALLO GETCWD (Carpeta borrada): Comportamiento Bash
		ft_putendl_fd("cd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory", 2);
		tmp_pwd = get_env_path(*env, "PWD", 3); //Const PWD lógic: oldPWD+/+ Arg
		if (tmp_pwd && arg_path)
		{
			n_dir = ft_strjoindelimit(tmp_pwd, "/", arg_path);
			update_env_var(env, "PWD", n_dir);
			free(n_dir);
		}
	}
}

int	ft_cd(t_command *cmd, t_env **env)
{
	char	*cur_dir;
	char	*path;

	if (cmd->args[1] && cmd->args[2])
	{
		ft_putendl_fd("minishell: cd: too many arguments", 2);
		return (1);
	}
	path = get_target_path(cmd->args, *env);
	if (!path)
		return (1);
	cur_dir = getcwd(NULL, 0);
	if (chdir(path) == -1)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		perror(path);
		if (cur_dir)
			free(cur_dir);
		return (1);
	}
	update_pwds(env, cur_dir, path); //añadir path si usams la chetada
	return (0);
}

