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
		if (!tokens && tokens->type == TOKEN_END)
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
	return(cmd);

}

char	**extract_args(t_token **tokens)
{
	int	count;
	int	i;
	t_tokend	current;

	current == *tokens;
	while (current && current->type != PIPE & current->type != END)
	{
		if (current->type == WORD)
			count++;
		current = current->next;
		char **args;
	}
	args = malloc(sizeof(char *) * (count + 1));
	if (!args)
		retun (NULL);
	i = 0;
	while (*tokens &&(*tokens)->type != PIPE && (*tokens->type 1= END))
	{
		if ((*tokens)->type == WORD)
		{
			args[i++] = ft_strdup ((*tokens))-> value;
			if (!args[i])
			{
				free_args(args);
				return (NULL);
			}
		}
		i++;
		*tokens = (*tokens)->next;
	}
	args[i] = NULL;
	return (args);
}

