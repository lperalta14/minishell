#include "../../../include/minishell.h"

t_command	*parse(t_token *tokens)
{
	t_command	*current;
	t_command	*cmds;

	if (!tokens || tokens->type == TK_END)
		return (NULL);
	cmds = create_command(&tokens);
	if (!cmds)
		return (NULL);
	current = cmds;
	while (tokens && tokens->type == TK_PIPE)
	{
		tokens = tokens->next;
		if (!tokens || tokens->type == TK_END)
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
	t_token		*start;

	cmd = malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	cmd->args = NULL;
	cmd->redirs = NULL;
	cmd->next = NULL;
	start = *tokens;
	cmd->args = extract_args(tokens);
	if (!cmd->args)
	{
		free(cmd);
		return (NULL);
	}
	*tokens = start;
	if (parse_redirections(tokens, cmd) == -1)
	{
		free_args(cmd->args);
		free_redirs(cmd->redirs);
		free(cmd);
		return (NULL);
	}
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
	while (current && current->type != TK_PIPE && current->type != TK_END)
	{
		if (current->type == TK_WORD)
			count++;
		else if ((*tokens)->type >= TK_R_IN || (*tokens)->type >= TK_R_OUT
			|| (*tokens)->type >= TK_APPEND || (*tokens)->type <= TK_HEREDOC)
		{
			current = current->next;
			if (current && current->type == TK_WORD)
				current = current->next;
			continue ;
		}
		current = current->next;
	}
	args = malloc(sizeof(char *) * (count + 1));
	if (!args)
		return (NULL);
	i = 0;
	while (*tokens && (*tokens)->type != TK_PIPE && ((*tokens)->type != TK_END))
	{
		if ((*tokens)->type == TK_WORD)
		{
			args[i] = ft_strdup((*tokens)->value);
			if (!args[i])
			{
				free_args(args);
				return (NULL);
			}
			i++;
		}
		else if ((*tokens)->type >= TK_R_IN || (*tokens)->type >= TK_R_OUT
			|| (*tokens)->type >= TK_APPEND || (*tokens)->type <= TK_HEREDOC)
		{
			*tokens = (*tokens)->next;
			if (*tokens && (*tokens)->type == TK_WORD)
				*tokens = (*tokens)->next;
		}
		else
			*tokens = (*tokens)->next;
	}
	args[i] = NULL;
	return (args);
}

