#include "../../include/minishell.h"

int	join_quote(t_lexer_state *st, t_token **tokens)
{
	t_token	*last;
	t_token	*new_token;
	char	prequote;

	prequote = '\0';
	if(st->pos > 0)
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
		&& !is_operator(st->input[st->pos]) && !isspace(st->input[st->pos]))
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

t_token	*init_token(char *line, t_token *tokens, t_env *env)
{
	t_lexer_state	*st;

	st = malloc(sizeof(t_lexer_state));
	if (!st)
		return (NULL);
	st->input = line;
	st->env = env;
	st->pos = 0;
	st->elimquote = 0;
	st->len = ft_strlen(line);
	tokens = tokenize(tokens, st);
	free(st);
	return (tokens);
}
/*
BACKTRACKING 🎯
Concepto clave:
Cuando encuentras una comilla (" o '):

Guardas la posición actual (checkpoint)
Intentas encontrar la comilla de cierre
Si la encuentras → Éxito, creas token con el tipo de comilla
Si NO la encuentras → BACKTRACK: vuelves al checkpoint y tratas
la comilla como un carácter normal
*/

/*
Detalles importantes:

En comillas dobles ", el backslash \ escapa el siguiente carácter
En comillas simples ', NO hay escapes, todo es literal
*/

/*
Jerarquía de comillas
La jerarquía que quieres:

Comillas dobles tienen prioridad
Comillas simples
Sin comillas

¿Pero qué significa esto en la práctica?
Cuando estás dentro de comillas dobles, las simples son literales:
"texto con 'simples'" → una sola palabra
Cuando estás dentro de comillas simples, las dobles son literales:
'texto con "dobles"' → una sola palabra
Pero ojo: la jerarquía aplica cuando estás buscando qué comilla abrir.
Si encuentras primero ", buscas su cierre ignorando ' intermedias.
Pregunta: ¿Ves la diferencia entre "jerarquía de apertura"
y "anidamiento"? No es lo mismo.
*/
