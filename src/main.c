#include "../include/minishell.h"

static void	minishell(char *input, t_env *env)
{
	t_token		*tokens;
	t_command	*cmds;

	tokens = NULL;
	tokens = init_token(input, tokens, env);
	//tokens = tokenize(input);
	print_tokens(tokens);
	cmds = parse(tokens);
	if (cmds)
	{
		print_commands(cmds);
		free_commands(cmds);
	}
	if (tokens)
		free_tokens(tokens);
}

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	t_env	*env_list;

	env_list = init_env(envp);
	if (isatty(STDIN_FILENO))
		print_banner("banners/acrobata.txt");
	while (1)
	{
		if (isatty(STDIN_FILENO))
			input = readline("minihell> ");
		else
			input = readline("");
		if (!input)
		{
			if (isatty(STDIN_FILENO))
				print_banner("banners/bye.txt");
			break ;
		}
		add_history(input);
		minishell(input, env_list);
		free(input);
	}
	rl_clear_history();
	free_env_list(env_list);
	return (0);
}
