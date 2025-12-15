#include "../../include/minishell.h"

void	count_quote(t_lexer_state *st, char quote, int end)
{
	int	i;

	i = st->pos +1;
	st->elimquote = 0;
	while (st->input[i] && i < end)
	{
		if (st->input[i] == quote)
			st->elimquote ++;
		i++;
	}
}

void	clean_quote(char *str, t_lexer_state *st, int end, char quote)
{
	int	i;

	i = st->pos;
	while (st->input[i] && i <= end)
	{
		if (quote == '"' && st->input[i] == '\\')
		{
			i++;
			*str++ = st->input[i];
		}
		else if (st->input[i] != quote)
			*str++ = st->input[i];
		i++;
	}
	*str = 0;
}

char	*clean_scape(char *dst, char *src, int len)
{
	int	del;
	int	i;

	i = 0;
	del = 0;
	while (src[i] && i < len)
	{
		if (src[i] == '\\' && src[i + 1] == '"')
			del ++;
		i++;
	}
	dst = ft_calloc(len - del + 1, sizeof(char));
	if (!dst)
		return (NULL);
	i = 0;
	del = 0;
	while (src[i] && i < len)
	{
		if (src[i] == '\\' && src[i + 1] == '"')
			i ++;
		dst[del] = src[i];
		del++;
		i++;
	}
	return (dst);
}

int	join_quote(t_lexer_state *st, t_token **tokens)
{
	t_token	*last;
	t_token	*new_token;
	char	prequote;

	prequote = '\0';
	if (st->pos > 0)
		prequote = st->input[st->pos - 1];
	last = last_token(*tokens);
	if (is_valid_quote(st->input, st->pos) == 1)
		new_token = try_extract_quoted(st);
	else
		new_token = extract_word(st);
	if (!new_token)
		return (1);
	if (last && last->type == TK_WORD && st->pos > 0 && prequote != ' ')
	{
		last->value = join_token_value(last->value, new_token->value);
		free(new_token);
	}
	else
		add_token(tokens, new_token);
	return (0);
}
