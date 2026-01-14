#include "../../include/minishell.h"

t_env	*get_env_node(char *str)
{
	t_env	*env;
	char	*pos_eq;
	int		key_len;

	env = malloc(sizeof(t_env));
	if (!env)
		return (NULL);
	pos_eq = ft_strchr(str, '=');
	if (pos_eq)
	{ // Caso: CLAVE=VALOR
		key_len = pos_eq - str; //aritmetica de punteros
		env->key = ft_substr(str, 0, key_len);
		env->value = ft_strdup(pos_eq + 1); //cpy dsd = por eso el +1
	}
	else
	{ //caso CLAVE sin valor.
		env->key = ft_strdup(str);
		env->value = NULL;
	}
	if (!env->key || (pos_eq && !env->value))
		free_env_list(env);
	env->next = NULL;
	return (env);
}

static void	force_env_var(t_env **head, char *key, char *value)
{
	t_env	*node;
	char	*full;

	node = *head;
	while (node)
	{
		if (ft_strcmp(node->key, key) == 0)
			return ;
		node = node->next;
	}
	if (value) //no existe, la creamos
		full = ft_strjoindelimit(key, "=", value);
	else
		full = ft_strdup(key); //caso raro sin valor
	if (full)
	{
		add_env(head, get_env_node(full));
		free(full);
	}
}

static void	update_shlvl(t_env **head)
{
	t_env	*tmp;
	int		lvl;

	tmp = find_env(*head, "SHLVL");
	if (tmp && tmp->value)
	{
		lvl = ft_atoi(tmp->value) + 1;
		if (lvl < 0)
			lvl = 0;
		free(tmp->value);
		tmp->value = ft_itoa(lvl);
	}
	else
		force_env_var(head, "SHLVL", "1");
}

t_env	*init_env(char **envp)
{
	t_env	*head;
	t_env	*n_env;
	int		i;
	char	*cwd;

	head = NULL;
	i = 0;
	while (envp[i])
	{
		n_env = get_env_node(envp[i]);
		if (!n_env)
		{
			free_env_list(head);
			return (NULL);
		}
		add_env(&head, n_env);
		i++;
	}
	cwd = getcwd(NULL, 0);
	force_env_var(&head, "PWD", cwd);
	if (cwd)
		free(cwd);
	update_shlvl(&head);
	force_env_var(&head, "_", "/usr/bin/env");
	return (head);
}

char	**env_to_array(t_env *env)
{
	int		count;
	char	**l_envs;
	t_env	*tmp;
	int		i;

	count = env_size(env);
	l_envs = malloc((count + 1) * sizeof(char *));
	if (!l_envs)
		return (NULL);
	i = 0;
	tmp = env;
	while (tmp)
	{
		l_envs[i] = ft_strjoindelimit(tmp->key, "=", tmp->value);
		if (!l_envs[i])
		{
			ft_freematrix(l_envs);
			return (NULL);
		}
		tmp = tmp->next;
		i++;
	}
	l_envs[i] = NULL;
	return (l_envs);
}
