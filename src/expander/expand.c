#include "../../include/lexer.h"

char	*extract_var_name(char *str, int *i)
{
	int		start;
	char	*name;

	//printf("extract_var_name str:%s, i: %i\n", str, *i);
	name = extract_special_var(str[*i], i);
	//printf("extract_specialvar name:%s, i: %i\n", name, *i);
	if (name)
		return (name);
	if (!ft_isalpha(str[*i]) && str[*i] != '_')
		return (NULL);
	//printf("extract_var_name str:%s, i: %i\n", str, *i);
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
	//printf("copy_var_value str:%s, var name:%s\n", src, var_name);
	value = get_env_value(env, var_name);
	//printf("value str:%s\n", value);
	len = 0;
	if (value)
	{
		//printf("pre strlcpy value:%s, dst:%s\n", value, dst);
		ft_strlcpy(dst, value, ft_strlen(value) + 1);
		//printf("post strlcpy value:%s, dst:%s\n", value, dst);
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
	//printf("LLEGO AQUI? str:%s\n", str);
	copy_expanded_content(expanded, str, env);
	return (expanded);
}

void	expand_variables(char **str, t_quote_type quote, t_env *env)
{
	char	*tmp;

	//printf("entro expand variable str:%s\n", *str);
	if (!str || !*str || quote == QUOTE_SINGLE)
		return ;
	tmp = build_expanded_string(*str, env);
	//printf("despues de build_expanded_string tmp:%s\n", tmp);
	if (!tmp)
		return ;
	free(*str);
	*str = tmp;
}