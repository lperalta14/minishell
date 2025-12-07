#include "../../include/lexer.h"

void	skip_spaces(t_lexer_state *state)
{
	while (state->pos < state->len && (state->input[state->pos] == ' '
			|| state->input[state->pos] == '\t'))
		state->pos++;
}

int	is_operator(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

int	 is_word(char c)
{
	if (!is_operator(c) && !is_quote(c) && !isspace(c))
		return (1);
	return (0);
}

t_token	*createtoken(t_token_type type, char *value)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	token->quote = QUOTE_NONE;
	if (value)
	{
		token->value = ft_strdup(value);
		if (!token->value)
		{
			free(token);
			return (NULL);
		}
	}
	else
		token->value = NULL;
	token->next = NULL;
	return (token);
}

void	add_token(t_token **head, t_token *new)
{
	t_token	*tmp;

	if (!*head)
	{
		*head = new;
		return ;
	}
	tmp = *head;
	while (tmp-> next)
		tmp = tmp->next;
	tmp->next = new;
}

t_token *last_token(t_token *tokens)
{
	if (!tokens)
		return (NULL);
	while (tokens->next)
		tokens = tokens->next;
	return (tokens);
}

char	*join_token_value(char *old, char *add)
{
	char	*joined;
	size_t	len_old;
	size_t	len_add;

	if (!old && !add)
		return (NULL);
	if (!old)
	{
		joined = ft_strdup(add);
		free(add);
		return (joined);
	}
	if (!add)
		return (old);
	len_old = ft_strlen(old);
	len_add = ft_strlen(add);
	joined = malloc(len_old + len_add + 1);
	if (!joined)
		return (free(add), old);
	ft_memcpy(joined, old, len_old);
	ft_memcpy(joined + len_old, add, len_add);
	joined[len_old + len_add] = '\0';
	free(old);
	free(add);
	return (joined);
}

void count_quote(t_lexer_state *st, char quote, int end)
{
	int	i;

	i = st->pos +1;
	st->elimquote = 0;
	while(st->input[i] && i < end)
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
	while(st->input[i] && i <= end)
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

char *clean_scape(char *dst, char *src, int len)
{
	int	del;
	int	i;

	i = 0;
	del = 0;
	//ft_printf("%i->len\n", len);
	while (src[i] && i < len)
	{
		if (src[i] == '\\' && src[i+1] == '"')
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
		//ft_printf("src %s i %i len %i dst %s\n", src+i, i, len, dst);
		if (src[i] == '\\' && src[i+1] == '"')
			i ++;
		dst[del] = src[i];
		del++;
		i++;
	}
	return (dst);
}
