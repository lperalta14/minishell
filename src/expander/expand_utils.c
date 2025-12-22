#include "../../include/lexer.h"

char	*get_env_value(t_env *env, char *key)
{
	if (ft_strcmp(key, "?") == 0)
	return (ft_itoa(g_exit_status));
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

int	has_dollar(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

char	*extract_special_var(char c, int *i)
{
	(i)++;
	if (c == '?')
		return (ft_strdup("?")); //esto debería cambiarse por el valor de la señal? mirarlo muy bien, de momento funciona porque devuelve'?'.
	if (c == '$')
		return (ft_strdup("$"));
	return (NULL);
}

int	get_var_value_len(char *str, int *i, t_env *env)
{
	char	*var_name;
	char	*value;
	int		len;

	(*i)++;
	var_name = extract_var_name(str, i);
	if (!var_name)
		return (1);
	value = get_env_value(env, var_name);
	len = 0;
	if (value)
		len = ft_strlen(value);
	free(var_name);
	return (len);
}

void	copy_expanded_content(char *dst, char *src, t_env *env)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (src[i])
	{
		if (src[i] == '$' && src[i + 1])
			j += copy_var_value(dst + j, src, &i, env);
		else
			dst[j++] = src[i++];
	}
	dst[j] = '\0';
}
