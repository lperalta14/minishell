#include "minishell.h"

void	create_redir(t_redir type, char *file)
{
	t_redir	*redir;

	redir = malloc (sizeof(t_redir));
	if (!redir)
		return (NULL);
	redir->type = type;
	redir->file = ft_strdup(file);
	if (!redir->file)
	{
		free(redir);
		return (NULL);
	}
	redir->next = NULL;
	return (redir);
}

void	add_redir(t_redir head, t_redir new)
{
	t_redir	current;

	if (!new)
		return ;
	if (!head)
	{
		head = new;
		return ;
	}
	current = head;
	while (current->next)
		current = current->next;
	current->next = new;
}
void	parse_redirections(t_token *tokens, char *cmd);
