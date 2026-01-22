#include "../../include/minishell.h"

/* int	ft_pwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		perror("pwd");
		return (1);
	}
	ft_printf("%s\n", cwd);
	free (cwd);
	return (0);
} */

int	ft_pwd(t_command *cmd, t_env **env)
{
    char	*cwd;
    char	*env_pwd;

    (void)cmd; // Argumentos ignorados en pwd básico
    cwd = getcwd(NULL, 0);
    if (cwd)
    {
        ft_printf("%s\n", cwd);
        free(cwd);
        return (0);
    }
    
    // Caso "Carpeta Borrada": getcwd falla, pero Bash imprime el PWD lógico
    env_pwd = get_env_path(*env, "PWD", 3);
    if (env_pwd)
    {
        ft_printf("%s\n", env_pwd);
        return (0);
    }
    
    // Si falla todo
    perror("minishell: pwd");
    return (1);
}

//OJO!! QUE NO HE PROBADO ESTE BICHARRACO, 
//PERO POR SI QUIERES REFACTORIZAR Y DECIR QUE LA TENEMOS ENORME. SI NO SE BORRA



