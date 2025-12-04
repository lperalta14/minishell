#include "../../include/lexer.h"

static int	is_closing_quote(char *str, int i, char quote)
{
	if (str[i] == quote)
		return (1);
	return (0);
}

static int	handle_escape(char *str, int i, char quote)
{
	if (quote == '"' && str[i] == '\\' && str[i + 1] != '\0')
		return (2);
	return (1);
}

static int	find_closing_quote(t_lexer_state *st, char quote)
{
	int	i;
	int	step;

	i = st->pos + 1;
	while (st->input[i])
	{
		step = handle_escape(st->input, i, quote);
		if (step == 2)
			i += 2;
		else if (is_closing_quote(st->input, i, quote))
		{
			if (st->input[i+1] != ' ' && !is_operator(st->input[i+1])
				&& st->input[i+1] != quote)
			{
				st->elimquote = i++;
				while (!isspace(st->input[i]) && !is_operator(st->input[i+1])
				&& st->input[i+1] != quote)
					i++;
			}
			return (i);
		}
		else
			i++;
	}
	return (-1);
}

static char	*extract_quoted_value(t_lexer_state *st, int end)
{
	int		len;
	char	*str;
	char	quote;

	quote = st->input[st->elimquote];
	len = end - st->pos;
	if (st->elimquote)
	{
		count_quote(st, quote, end);
		len = len - st->elimquote;
		str = malloc(sizeof(char) * len + 1);
		if (!str)
			return (NULL);
		clean_quote(str, st, end, quote);
	}
	else
	{
		str = malloc(sizeof(char) * len + 1);
		if (!str)
			return (NULL);
		ft_strlcpy(str, st->input + st->pos + 1, len);
	}
	return (str);
}

t_token	*try_extract_quoted(t_lexer_state *st)
{
	int		end;
	char	quote;
	char	*value;
	t_token	*token;

	quote = st->input[st->pos];
	end = find_closing_quote(st, quote);
	if (end == -1)
		return (0);
	value = extract_quoted_value(st, end);
	if (!value)
		return (NULL);
	token = createtoken(TOKEN_WORD, value);
	free(value);
	if (!token)
		return (NULL);
	if (quote == '"')
		token->quote = QUOTE_DOUBLE;
	else
		token->quote = QUOTE_SINGLE;
	st->pos = end + 1;
	return (token);
}
