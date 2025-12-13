#include "../../include/lexer.h"

int	join_quote(t_lexer_state *st, t_token **tokens)
{
	t_token	*last;
	t_token	*new_token;
	char	prequote;

	//if (st->pos > 0)
	//t_printf("entro en join quote\n");
	prequote = '\0';
	if(st->pos > 0)
		prequote = st->input[st->pos - 1];
	last = last_token(*tokens);
	new_token = try_extract_quoted(st);
	if (!new_token)
		return (1);
	if (last && last->type == TK_WORD && st->pos > 0 && prequote != ' ')
	{
		//ft_printf("17prejoin new; %s  last; %s\n", new_token->value, last->value);
		last->value = join_token_value(last->value, new_token->value);
		//ft_printf("19postjoin; %s\n", last->value);
		//free(new_token->value);
		//if (last->quote == QUOTE_NONE )
		free(new_token);
	}
	else
		add_token(tokens, new_token);
	//ft_printf("salgo aquí\n");
	return (0);
}

t_token	*tokenize(t_token *tokens, t_lexer_state *st)
{
	//t_token	*tokens;
	//t_lexer_state *st;

	//tokens = NULL;
	/*st = malloc(sizeof(t_lexer_state));
	if (!st)
		return (NULL);
	st->input = line;
	st->pos = 0;
	st->len = ft_strlen(line);*/
	while (st->pos < st->len)
	{
		skip_spaces(st);
		if (st->pos >= st->len)
			break ;
		if (is_operator(st->input[st->pos]))
			check_operator(st, &tokens);
		else if (is_valid_quote(st->input, st->pos) == 1)
		{
			//ft_printf("char; %c pos;%i\n", st->input[st->pos], st->pos);
			if (join_quote(st, &tokens))
			{
				ft_printf("syntax error\n");
				free_tokens(tokens);//cambiar esto por una funcion que libere bien los tokens.
				return (NULL);
			}
		}
		else
		{
			//ft_printf("entro en extract_word\n");
			extract_word(st, &tokens);
			//ft_printf("salgo de extract: %s\n", st->input+st->pos);
		}
	}
	//free(st);
	return (tokens);
}

void	extract_word(t_lexer_state *st, t_token **tokens)
{
	int		start;
	//int		len;
	char	*word;
	t_token	*token;

	start = st->pos;
	//len = 0;
	word = NULL;
	while (st->pos < st->len && (is_valid_quote(st->input, st->pos) != 1)
		&& !is_operator(st->input[st->pos]) && !isspace(st->input[st->pos]))
	{
		//len++;
		st->pos++;
		//ft_printf("start; %i  count position; %i\n", start, st->pos);
	}
	if (ft_memchr(st->input + start, '\\', st->pos - start))
	{
		//ft_printf("start; %i, len: %i st: %s\n", start, len, (st->input + start));
		word = clean_scape(word, st->input + start, st->pos - start);
		//ft_printf("post strchr %s\n", word);
	}
	else
		word = ft_substr(st->input, start, st->pos - start);
	if (!word)
		return ;
	token = createtoken(TK_WORD, word);
	if (token)
		token->quote = QUOTE_NONE;
	add_token(tokens, token);
	free(word);
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

t_token	*init_token(char *line, t_token *tokens, char **env)
{
	t_lexer_state	*st;

	st = malloc(sizeof(t_lexer_state));
	if (!st)
		return (NULL);
	st->input = line;
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
