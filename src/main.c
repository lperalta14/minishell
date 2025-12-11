#include "../include/minishell.h"

void	minishell(char *input)
{
	t_token		*tokens;
	t_command	*cmds;

	tokens = NULL;
	tokens = init_token(input, tokens);
	if (!validate_syntax(&tokens))
	{
		free_tokens(tokens);
		return ;
	}
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

	(void)argc;
	(void)argv;
	env_list = init_env(envp);
	// TODO: Inicializar señales (signal/sigaction)
	if (isatty(STDIN_FILENO))
		print_banner("banners/acrobata.txt");
	while (1)
	{
		input = readline("minishell> ");
		if (!input)
		{
			if (isatty(STDIN_FILENO))
				print_banner("banners/bye.txt");
			break ;
		}
		if (input[0] != '\0')
			add_history(input);
		minishell(input);
		free(input);
	}
	rl_clear_history();
	free_env_list(env_list);
	return (0);
}
