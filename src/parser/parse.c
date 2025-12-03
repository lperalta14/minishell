#include "../../../include/minishell.h"

t_command	*parse(t_token *tokens)
{
	t_command	*current;
	t_command	*cmds;

	if (!tokens || tokens->type == TOKEN_END)
		return (NULL);
	cmds = create_command(&tokens);
	if (!cmds)
		return (NULL);
	current = cmds;
	while (tokens && tokens->type == TOKEN_PIPE)
	{
		tokens = tokens->next;
		if (!tokens || tokens->type == TOKEN_END)
		{
			free_commands(cmds);
			return (NULL);
		}
		current->next = create_command(&tokens);
		if (!current->next)
		{
			free_commands(cmds);
			return (NULL);
		}
		current = current->next;
	}
	return (cmds);
}

t_command	*create_command(t_token **tokens)
{
	t_command	*cmd;

	cmd = malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	cmd->args = NULL;
	cmd->redirs = NULL;
	cmd->next = NULL;
	cmd->args = extract_args(tokens);
	if (!cmd->args)
	{
		free(cmd);
		return (NULL);
	}
	//parsear redirecciones(opcional por ahora);
	//parse_redirections(tokens, cmd);
	return (cmd);

}

char	**extract_args(t_token **tokens)
{
	int		count;
	int		i;
	t_token	*current;
	char	**args;

	current = *tokens;
	count = 0;
	while (current && current->type != TOKEN_PIPE && current->type != TOKEN_END)
	{
		if (current->type == TOKEN_WORD)
			count++;
		else if (current->type >= TOKEN_REDIR_IN
			&& current->type <= TOKEN_REDIR_HEREDOC)
		{
			current = current->next;
			if (current && current->type == TOKEN_WORD)
				current = current->next;
			continue ;
		}
		current = current->next;
	}
	args = malloc(sizeof(char *) * (count + 1));
	if (!args)
		return (NULL);
	i = 0;
	while (*tokens && (*tokens)->type != TOKEN_PIPE
		&& ((*tokens)->type != TOKEN_END))
	{
		if ((*tokens)->type == TOKEN_WORD)
		{
			args[i] = ft_strdup((*tokens)->value);
			if (!args[i])
			{
				free_args(args);
				return (NULL);
			}
			i++;
		}
		else if ((*tokens)->type >= TOKEN_REDIR_IN
			&& (*tokens)->type <= TOKEN_REDIR_HEREDOC)
		{
			*tokens = (*tokens)->next;
			if (*tokens && (*tokens)->type == TOKEN_WORD)
				*tokens = (*tokens)->next;
		}
		else
			*tokens = (*tokens)->next;
	}
	args[i] = NULL;
	return (args);
}

