#include "../../include/lexer.h"

static int	is_closing_quote(char *str, int i, char quote)
{
	if (str[i] == quote && is_valid_quote(str, i) == 1)
		return (1);
	return (0);
}

/*static int	handle_escape(char *str, int i, char quote)
{
	if (quote)
	if (str[i+1] == '"' && str[i] == '\\')
		return (2);
	return (1);
}*/

static int	find_closing_quote(t_lexer_state *st, char quote)
{
	int	i;
	//int	step;

	i = st->pos + 1;
	while (st->input[i])
	{
		if (is_valid_quote(st->input, st->pos) == 2)
		{ //ft_printf("entro is valid; %i\n", i);
				i++;
		}
		else if (is_closing_quote(st->input, i, quote))
		{
			//ft_printf("entro en is closing; %i\n", i);
			while (st->input[i + 1] && st->input[i + 1] != ' '
				&& !is_operator(st->input[i + 1])
				&& is_valid_quote(st->input, st->pos + 1) != 1)
			{
				st->elimquote = i;
				/*while (st->input[i+1] && !isspace(st->input[i+1])
				&& !is_operator(st->input[i+1]) && st->input[i+1] != quote)*/
				i++;
			}
			return (i);
		}
		else
			i++;
	}
	return (-1);
}

static char	*extract_quoted_value(t_lexer_state *st, int end, char quote)
{
	int		len;
	char	*str;

	str = NULL;
	len = end - st->pos;
	//ft_printf("entro en extract quote en pos: %i\n", st->pos);
	if (st->elimquote)
	{
		count_quote(st, quote, end);
		len = len - st->elimquote;
		str = malloc(sizeof(char) * len + 1);
		if (!str)
			return (NULL);
		//ft_printf("preclean dst: %s/ src: %s/\n", str, st->input+st->pos);
		clean_quote(str, st, end, quote);
		//ft_printf("postclean dst: %s/ src: %s/\n", str, st->input+st->pos);
	}
	else
	{
		/*str = malloc(sizeof(char) * len + 1);
		if (!str)
			return (NULL);*/
		str = clean_scape(str, st->input + st->pos + 1, len - 1);
		//ft_printf("postctrlcpy dst: %s/ src: %s/\n", str, st->input+st->pos);
	}
	return (str);
}

t_token	*try_extract_quoted(t_lexer_state *st)
{
	int		end;
	char	quote;
	char	*value;
	t_token	*token;

	//ft_printf("entro en tryextract\n");
	quote = st->input[st->pos];
	if (quote == '"')
		st->quote = QUOTE_DOUBLE;
	else
		st->quote = QUOTE_SINGLE;
	end = find_closing_quote(st, quote);
	//ft_printf("end %i\n", end);
	if (end == -1)
		return (0);
	value = extract_quoted_value(st, end, quote);
	if (!value)
		return (NULL);
	token = createtoken(TK_WORD, value);
	free(value);
	if (!token)
		return (NULL);
	token->quote = st->quote;
	/*if (quote == '"')
		token->quote = QUOTE_DOUBLE;
	else
		token->quote = QUOTE_SINGLE;*/
	st->pos = end + 1;
	//ft_printf("pos en try; %i\n", st->pos);
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