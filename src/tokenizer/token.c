
#include "../../include/lexer.h"
/*
🎯 Mi recomendación de orden REAL

✅ Termina add_token()
✅ Añade t_quote_type a las estructuras
✅ Crea tokenize() básico que solo detecte operadores y palabras SIN comillas
✅ Crea print_tokens() para debug
✅ Prueba con strings simples: "ls | grep hola"
✅ Implementa try_extract_quoted() con backtracking
✅ Integra el manejo de comillas en tokenize()
✅ Prueba casos complejos

*/

tokenize()
{
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
	token->value = ft_strdup(value);
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

/**
 * @brief Construct a new check operator object
 * 
 * @param state 
 */
check_operator(t_lexer_state *state)
{
	char	c;

	c = state->input[state->pos];
	while (c)
	{
		if (c == '|')
		{
			t_token *token = createtoken(TOKEN_PIPE, "|");
			add_token( head, token);
			state->pos++;
		}
		if (c == '<' && state->input[state->pos+1] == '<')
		{
			t_token *token = createtoken(TOKEN_APPEND, "<<");
			add_token( head, token);
			state->pos += 2;
		}
		else
		{
			t_token *token = createtoken(TOKEN_REDIR_IN , "<");
			add_token( head, token);
			state->pos++;
		}
		if (c == '>' && state->input[state->pos+1] == '>')
		{
			t_token *token = createtoken(TOKEN_HEREDOC, ">>");
			add_token( head, token);
			state->pos += 2;
		}
		else
		{
			t_token *token = createtoken(TOKEN_REDIR_OUT, ">");
			add_token( head, token);
			state->pos++;
		}
	}
}

/**
 * @brief Construct a new extract word object
 * 
 * @param state 
 */
extract_word(t_lexer_state *state)
{
Debe:

Leer caracteres mientras no sean espacios ni operadores
Crear un string con esos caracteres
Crear un token TOKEN_WORD con quote = QUOTE_NONE
Avanzar posición
}

/*
BACKTRACKING 🎯
Concepto clave:
Cuando encuentras una comilla (" o '):

Guardas la posición actual (checkpoint)
Intentas encontrar la comilla de cierre
Si la encuentras → Éxito, creas token con el tipo de comilla
Si NO la encuentras → BACKTRACK: vuelves al checkpoint y tratas la comilla como un carácter normal

Pregunta para ti: ¿Entiendes por qué esto es backtracking? Es como decir "a ver si funciona, y si no, deshago y pruebo otra cosa".
Función: try_extract_quoted(t_lexer_state *state, char quote_char)
Debe retornar:

El string extraído si tuvo éxito
NULL si falló (y entonces haces backtrack)

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