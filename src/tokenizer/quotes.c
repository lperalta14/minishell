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
	while (str[i] != '\0')
	{
		step = handle_escape(st->input, i, quote);
		if (step == 2)
			i += 2;
		else if (is_closing_quote(st->input, i, quote))
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

	len = end - st->pos - 1;
	str = malloc(len + 1);
	if (!str)
		return (NULL);
	ft_strlcpy(str, st->input + st->pos + 1, len + 1);
	return (str);
}

int	try_extract_quoted(t_lexer_state *st, t_token **tokens)
{
	int		end;
	char	quote;
	char	*value;

	quote = st->input[st->pos];
	end = find_closing_quote(st, quote);
	if (end == -1)
		return (0);
	value = extract_quoted_value(st, end);
	if (!value)
		return (0);
	if (quote == '"')
		add_token(tokens, createtoken(TOKEN_DQUOTE, value));
	else
		add_token(tokens, createtoken(TOKEN_SQUOTE, value));
	free(value);
	st->pos = end + 1;
	return (1);
}
