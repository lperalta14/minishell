
#include "../../include/lexer.h"
/*
🎯 Mi recomendación de orden REAL

✅ Termina add_token()
✅ Añade t_quote_type a las estructuras
 Crea tokenize() básico que solo detecte operadores y palabras SIN comillas
 Crea print_tokens() para debug
 Prueba con strings simples: "ls | grep hola"
 Implementa try_extract_quoted() con backtracking
 Integra el manejo de comillas en tokenize()
 Prueba casos complejos

*/

void	extract_word(t_lexer_state *state, t_token **tokens)
{
	int		start;
	int		len;
	char	*word;
	t_token	*token;

	start = state->pos;
	len = 0;
	while (state->pos < state->len && !is_operator(state->input[state->pos])
		&& state->input[state->pos] != ' ' && state->input[state->pos] != '\t')
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

void	tokenize()
{
	t_token	*tokens;
	t_lexer_state *state;

	state = NULL;
	state->pos = 0;
	while (state->pos < state->len)
	{
		skip_spaces(state);
		if (is_operator(state->input[state->pos]))
			check_operator(state, &tokens);
		else if ((state->input[state->pos] == '\"') || (state->input[state->pos] == '\''))
			try_extract_quoted(state, &tokens, NULL);
		else
			extract_word(state, &tokens);
	}
}
/*
	mientras no llegues al final del string:
	- saltar espacios
	- si es operador → crear token operador
	- si es comilla → intentar extraer con backtracking
		- si falla → tratar como palabra normal
	- si no → extraer palabra normal
*/
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
