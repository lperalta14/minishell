#include "../../include/lexer.h"

char	*extract_var_name(char *str, int *i)
{
	int		start;
	char	*name;

	name = extract_special_var(str[*i], i);
	if (name)
		return (name);
	if (!ft_isalpha(str[*i]) && str[*i] != '_')
		return (NULL);
	start = *i;
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
		(*i)++;
	return (ft_substr(str, start, *i - start));
}

int	calculate_expanded_len(char *str, t_env *env)
{
	int		len;
	int		i;

	len = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1])
			len += get_var_value_len(str, &i, env);
		else
		{
			len++;
			i++;
		}
	}
	return (len);
}

int	copy_var_value(char *dst, char *src, int *i, t_env *env)
{
	char	*var_name;
	char	*value;
	int		len;

	(*i)++;
	var_name = extract_var_name(src, i);
	if (!var_name)
	{
		dst[0] = '$';
		return (1);
	}
	value = get_env_value(env, var_name);
	len = 0;
	if (value)
	{
		ft_strlcpy(dst, value, ft_strlen(value) + 1);
		len = ft_strlen(value);
	}
	free(var_name);
	return (len);
}

static char	*build_expanded_string(char *str, t_env *env)
{
	char	*expanded;
	int		len;

	if (!str || !env)
		return (ft_strdup(str));
	len = calculate_expanded_len(str, env);
	expanded = malloc(sizeof(char) * (len + 1));
	if (!expanded)
		return (NULL);
	copy_expanded_content(expanded, str, env);
	return (expanded);
}

void	expand_variables(char **str, t_quote_type quote, t_env *env)
{
	char	*tmp;

	if (!str || !*str || quote == QUOTE_SINGLE)
		return ;
	tmp = build_expanded_string(*str, env);
	if (!tmp)
		return ;
	free(*str);
	*str = tmp;
}