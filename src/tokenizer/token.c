
#include "lexer.h"

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

check_operator(t_lexer_state *state)
{
	ver si el caracter actual es |, <, >, (, )
	si es > o <, mirar si el siguente tambien lo es (>>, <<)
	crear el token correspondiente
	Avanzar la posicion

	ORDEN DE IMPLEMENTACION
	 Pipe | (más fácil)
	 Parentesis ( y )
	 Redirecciones simples < y >
	 Redirecciones dobles >> y <<
}