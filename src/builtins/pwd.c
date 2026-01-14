#include "../../include/minishell.h"

int	ft_pwd(void)
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
}
//OJO!! QUE NO HE PROBADO ESTE BICHARRACO, 
//PERO POR SI QUIERES REFACTORIZAR Y DECIR QUE LA TENEMOS ENORME. SI NO SE BORRA


// static void	update_pwds(t_env **env, char *cur_dir, char *arg_path)
// {
// 	char	*n_dir;
// 	char	*tmp_pwd;

// 	if (cur_dir)
// 	{
// 		update_env_var(env, "OLDPWD", cur_dir);
// 		free(cur_dir);
// 	}
// 	else // Si getcwd falló antes (carpborrada), intentamos usar el PWD del env
// 	{
// 		tmp_pwd = get_env_path(*env, "PWD", 3);
// 		if (tmp_pwd)
// 			update_env_var(env, "OLDPWD", tmp_pwd);
// 	}
// 	n_dir = getcwd(NULL, 0);
// 	if (n_dir)
// 	{
// 		update_env_var(env, "PWD", n_dir);
// 		free(n_dir);
// 	}
// 	else
// 	{ // 3. FALLO GETCWD (Carpeta borrada): Comportamiento Bash
// 		ft_putendl_fd("cd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory", 2);
// 		tmp_pwd = get_env_path(*env, "PWD", 3); //Const PWD lógic: oldPWD+/+ Arg
// 		if (tmp_pwd && arg_path)
// 		{
// 			n_dir = ft_strjoindelimit(tmp_pwd, "/", arg_path);
// 			update_env_var(env, "PWD", n_dir);
// 			free(n_dir);
// 		}
// 	}
// }