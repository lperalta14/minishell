#include "minishell.h"

int main(int argc, char **argv, char **envp)
{
	char	*input;

	if (argc > 0 || argv || envp)
	if (isatty(STDIN_FILENO))//para los test (isatty solo muestra el banner si es interactivo)
		print_banner("banners/acrobata.txt");
	while (1)
	{
		input = readline("minishell> ");
		if (!input)
		{
			if (isatty(STDIN_FILENO))
				print_banner("banners/bye.txt");
			break;;
		}
		add_history(input);
		printf("%s\n", input);
		free(input);
	}
	clear_history();
	rl_clear_history();
	return(0);
}
