
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
/**
 * @brief Salta espacios y tabulaciones en el input
 * 
 * @param state Estado del lexer con posición actual
 */
void	skip_spaces(t_lexer_state *state)
{
	while (state->pos < state->len && (state->input[state->pos] == ' '
			|| state->input[state->pos] == '\t'))
		state->pos++;

}

/**
 * @brief
 * 
 * @param
 */
int	is_operator(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

/**
 * @brief Construct a new extract word object
 * 
 * @param state
 * @param tokens Puntero a la lista de tokens
 */
void	*extract_word(t_lexer_state *state, t_token **tokens)
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

Debe:

Leer caracteres mientras no sean espacios ni operadores
Crear un string con esos caracteres
Crear un token TOKEN_WORD con quote = QUOTE_NONE
Avanzar posición

/**
 * @brief
 * 
 * @param
 */
tokenize()
{
	t_token	*tokens;
	t_lexer_state *state;

	while (state->pos < state->len)
	{
		skip_spaces(state);
		if (is_operator(state->input[state->pos]))
			addtoken(&tokens, createtoken(check_operator(state)))
		else if (is_quote(state->input[state->pos]))
			try_extract_quoted(state, &tokens);
		else
			extract_word(state, &tokens);
	}
	mientras no llegues al final del string:
	- saltar espacios
	- si es operador → crear token operador
	- si es comilla → intentar extraer con backtracking
		- si falla → tratar como palabra normal
	- si no → extraer palabra normal
}

/**
 * @brief 
 * 
 * @param type 
 * @param value 
 * @return t_token* 
 */
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

/**
 * @brief 
 * 
 * @param head 
 * @param new 
 */
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


/**
 * @brief Construct a new check operator object
 * 
 * @param state 
 */
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
	Debe retornar:

El string extraído si tuvo éxito
NULL
backtrack
char	*try_extract_quoted(t_lexer_state *state)
{
	int		start;
	int		i;
	char	quote;
	char	*result;

	quote = state->input[state->pos];
	start = state->pos;
	i = start + 1;
	while (i < state->len)
	{
		if (quote == '"' && state->input[i] == '\\'
			&& i + 1 < state->len)
		{
			i += 2;
			continue ;
		}
		if (state->input[i] == quote)
		{
			result = ft_substr(state->input, start + 1, i - (start + 1));
			state->pos = i + 1;
			return (result);
		}
		i++;
	}
	state->pos = start;
	return (NULL);
}

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
