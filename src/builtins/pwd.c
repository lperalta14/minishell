#include "../../include/minishell.h"

int ft_pwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		perror("pwd");
		return(1);
	}
	ft_printf("%s\n", cwd);
	free (cwd);
	return (0);
}