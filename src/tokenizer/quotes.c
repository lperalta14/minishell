#include "../../include/minishell.h"

static int	is_closing_quote(char *str, int i, t_quote_type quote)
{
	char	cquote;

	if (quote == 1)
		cquote = '"';
	else
		cquote = '\'';
	if (str[i] == cquote && is_valid_quote(str, i) == 1)
		return (1);
	return (0);
}

static int	find_closing_quote(t_lexer_state *st)
{
	int	i;

	i = st->pos + 1;
	while (st->input[i])
	{
		if (is_valid_quote(st->input, st->pos) == 2)
			i++;
		else if (is_closing_quote(st->input, i, st->quote))
			return (i);
		else
			i++;
	}
	return (-1);
}

static char	*extract_quoted_value(t_lexer_state *st, int end)
{
	int		len;
	char	*str;

	str = NULL;
	len = end - st->pos;
	str = clean_scape(str, st->input + st->pos + 1, len - 1);
	if (st->quote == QUOTE_DOUBLE && has_dollar(str))
		expand_variables(&str, QUOTE_DOUBLE, st->env);
	return (str);
}

t_token	*try_extract_quoted(t_lexer_state *st)
{
	int		end;
	char	*value;
	t_token	*token;

	if (st->input[st->pos] == '"')
		st->quote = QUOTE_DOUBLE;
	else
		st->quote = QUOTE_SINGLE;
	end = find_closing_quote(st);
	if (end == -1)
		return (0);
	value = extract_quoted_value(st, end);
	if (!value)
		return (NULL);
	token = createtoken(TK_WORD, value);
	free(value);
	if (!token)
		return (NULL);
	token->quote = st->quote;
	st->pos = end + 1;
	return (token);
}

int	is_valid_quote(char *str, int pos)
{
	if (str[pos] == '\'')
		return (1);
	else if (str[pos] == '"')
	{
		if (pos > 0 && str[pos -1] == '\\')
			return (2);
		else
			return (1);
	}
	return (0);
}
