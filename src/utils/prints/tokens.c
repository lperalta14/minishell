#include "minishell.h"

void	print_tokens(t_token *tokens)
{
t_token	*tmp = tokens;

printf("\n---- TOKENS ----\n");
while (tmp)
{
	printf("TYPE: %d | VALUE: \"%s\"\n", tmp->type, tmp->value);
	tmp = tmp->next;
}
printf("----------------\n\n");
}
