#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*input;

	(void)argc;
	(void)argv;
	(void)envp;
	if (isatty (STDIN_FILENO)) //test(solo muestra banner si es interactivo)
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
		add_history(input);
		printf("%s\n", input);
		free(input);
	}
	rl_clear_history(); //vers off +modern, cleanup neces, evita si mem issues,+simple y mantenible
	return (0);
}
