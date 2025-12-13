#include "../../../include/minishell.h"

void	free_env_list(t_env *head)
{
	t_env	*tmp;

	while (head)
	{
		tmp = head->next;
		if (head->key)
			free(head->key);
		if (head->value)
			free(head->value);
		free(head);
		head = tmp;
	}
}
