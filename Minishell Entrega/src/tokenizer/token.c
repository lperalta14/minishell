/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msedeno- <msedeno-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 20:16:33 by msedeno-          #+#    #+#             */
/*   Updated: 2026/01/23 17:16:27 by msedeno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_token	*init_token(char *line, t_token *tokens, t_env *env)
{
	t_lexer_state	*st;

	st = malloc(sizeof(t_lexer_state));
	if (!st)
		return (NULL);
	st->input = line;
	st->env = env;
	st->pos = 0;
	st->len = ft_strlen(line);
	tokens = tokenize(tokens, st);
	free(st);
	return (tokens);
}

t_token	*tokenize(t_token *tokens, t_lexer_state *st)
{
	while (st->pos < st->len)
	{
		skip_spaces(st);
		if (st->pos >= st->len)
			break ;
		if (is_operator(st->input[st->pos]))
			check_operator(st, &tokens);
		else
		{
			if (join_quote(st, &tokens))
			{
				ft_printf("syntax error\n");
				free_tokens(tokens);
				return (NULL);
			}
		}
	}
	return (tokens);
}

t_token	*extract_word(t_lexer_state *st)
{
	int		start;
	char	*word;
	t_token	*token;

	start = st->pos;
	word = NULL;
	while (st->pos < st->len && (is_valid_quote(st->input, st->pos) != 1)
		&& !is_operator(st->input[st->pos]) && !ft_isspace(st->input[st->pos]))
		st->pos++;
	if (ft_memchr(st->input + start, '\\', st->pos - start))
		word = clean_scape(word, st->input + start, st->pos - start);
	else
		word = ft_substr(st->input, start, st->pos - start);
	if (!word)
		return (NULL);
	if (has_dollar(word))
		expand_variables(&word, QUOTE_NONE, st->env);
	token = createtoken(TK_WORD, word);
	if (token)
		token->quote = QUOTE_NONE;
	free(word);
	return (token);
}

static void	operator_red(t_lexer_state *st, t_token **tokens)
{
	char	c;

	c = st->input[st->pos];
	if (c == '<' && st->input[st->pos + 1] == '<')
	{
		add_token(tokens, createtoken(TK_HEREDOC, "<<"));
		st->pos += 2;
	}
	else if (c == '<')
	{
		add_token(tokens, createtoken(TK_R_IN, "<"));
		st->pos++;
	}
	else if (c == '>' && st->input[st->pos + 1] == '>')
	{
		add_token(tokens, createtoken(TK_APPEND, ">>"));
		st->pos += 2;
	}
	else if (c == '>')
	{
		add_token(tokens, createtoken(TK_R_OUT, ">"));
		st->pos++;
	}
}

void	check_operator(t_lexer_state *st, t_token **tokens)
{
	char	c;

	c = st->input[st->pos];
	if (c == '|')
	{
		add_token(tokens, createtoken(TK_PIPE, "|"));
		st->pos++;
	}
	else if ((c == '<') || (c == '>'))
		operator_red(st, tokens);
}
