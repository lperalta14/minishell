
#include "../../include/lexer.h"
int	join_quote(t_lexer_state *st, t_token **tokens)
{
	t_token	*last;
	t_token	*new_token;
	char	prequote;

	prequote = st->input[st->pos - 1];
	last = last_token(*tokens);
	new_token = try_extract_quoted(st);
	if (!new_token)
		return (1);
	if (last && last->type == TOKEN_WORD && st->pos > 0 && prequote != ' ')
	{
		last->value = join_token_value(last->value, new_token->value);
		//free(new_token->value);
		free(new_token);
	}
	else
		add_token(tokens, new_token);
	return (0);
}

t_token	*tokenize(char *line)
{
	t_token	*tokens;
	t_lexer_state *state;

	tokens = NULL;
	state = malloc(sizeof(t_lexer_state));
	if (!state)
		return (NULL);
	state->input = line;
	state->pos = 0;
	state->len = ft_strlen(line);
	while (state->pos < state->len)
	{
		skip_spaces(state);
		if (state->pos >= state->len)
			break;
		if (is_operator(state->input[state->pos]))
			check_operator(state, &tokens);
		else if (is_quote(state->input[state->pos]))
		{
			if (join_quote(state, &tokens))
				break ;
		}
		else
			extract_word(state, &tokens);
	}
	free(state);
	return (tokens);
}

void	extract_word(t_lexer_state *state, t_token **tokens)
{
	int		start;
	int		len;
	char	*word;
	t_token	*token;

	start = state->pos;
	len = 0;
	while (state->pos < state->len && is_word(state->input[state->pos]))
	{
		len++;
		state->pos++;
	}
	word = ft_substr(state->input, start, len);
	if (!word)
		return ;
	token = createtoken(TOKEN_WORD, word);
	if (token)
		token->quote = QUOTE_NONE;
	add_token(tokens, token);
	free(word);
}

static void	operator_red(t_lexer_state *state, t_token **tokens)
{
	char	c;

	c = state->input[state->pos];
	if (c == '<' && state->input[state->pos + 1] == '<')
	{
		add_token(tokens, createtoken(TOKEN_HEREDOC, "<<"));
		state->pos += 2;
	}
	else if (c == '<')
	{
		add_token(tokens, createtoken(TOKEN_REDIR_IN, "<"));
		state->pos++;
	}
	else if (c == '>' && state->input[state->pos + 1] == '>')
	{
		add_token(tokens, createtoken(TOKEN_APPEND, ">>"));
		state->pos += 2;
	}
	else if (c == '>')
	{
		add_token(tokens, createtoken(TOKEN_REDIR_OUT, ">"));
		state->pos++;
	}
}


void check_operator(t_lexer_state *state, t_token **tokens)
{
	char	c;

	c = state->input[state->pos];

	if (c == '|')
	{
		add_token(tokens, createtoken(TOKEN_PIPE, "|"));
		state->pos++;
	}
	else if ((c == '<') || (c == '>'))
		operator_red(state, tokens);
}


/*
BACKTRACKING 🎯
Concepto clave:
Cuando encuentras una comilla (" o '):

Guardas la posición actual (checkpoint)
Intentas encontrar la comilla de cierre
Si la encuentras → Éxito, creas token con el tipo de comilla
Si NO la encuentras → BACKTRACK: vuelves al checkpoint y tratas la comilla como un carácter normal
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
Pero ojo: la jerarquía aplica cuando estás buscando qué comilla abrir. Si encuentras primero ", buscas su cierre ignorando ' intermedias.
Pregunta: ¿Ves la diferencia entre "jerarquía de apertura" y "anidamiento"? No es lo mismo.
*/
