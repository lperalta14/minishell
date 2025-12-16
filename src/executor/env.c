#include "../../include/minishell.h"

void	add_env(t_env **head, t_env *new)
{
	t_env	*current;

	if (!new)
		return ;
	if (!*head)
	{
		*head = new;
		return ;
	}
	current = *head;
	while (current->next)
		current = current->next;
	current->next = new;
}

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
		env->value = ft_strdup(pos_eq + 1); //copiar desde el = por eso el +1
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

t_env	*init_env(char **envp)
{
	t_env	*head;
	t_env	*n_env;
	int		i;

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
	return (head);
}

int	env_size(t_env *env)
{
	int	count;

	count = 0;
	while (env)
	{
		count++;
		env = env->next;
	}
	return (count);
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

