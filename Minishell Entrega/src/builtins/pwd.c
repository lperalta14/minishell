/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msedeno- <msedeno-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 20:14:16 by msedeno-          #+#    #+#             */
/*   Updated: 2026/01/23 17:13:52 by msedeno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_pwd(t_command *cmd, t_env **env)
{
	char	*cwd;
	char	*env_pwd;

	(void)cmd;
	cwd = getcwd(NULL, 0);
	if (cwd)
	{
		ft_printf("%s\n", cwd);
		free(cwd);
		return (0);
	}
	env_pwd = get_env_path(*env, "PWD", 3);
	if (env_pwd)
	{
		ft_printf("%s\n", env_pwd);
		return (0);
	}
	perror("minishell: pwd");
	return (1);
}

static void	set_oldpwd_env(t_env **env, char *cur_dir)
{
	char	*tmp;

	if (cur_dir)
		update_env_var(env, "OLDPWD", cur_dir);
	else
	{
		tmp = get_env_path(*env, "PWD", 3);
		if (tmp)
			update_env_var(env, "OLDPWD", tmp);
	}
}

static void	recover_lost_pwd(t_env **env, char *arg_path)
{
	char	*tmp;
	char	*new_path;

	ft_putstr_fd("cd: error retrieving current directory: getcwd: ", 2);
	ft_putstr_fd("cannot access parent directories: ", 2);
	ft_putendl_fd("No such file or directory", 2);
	tmp = get_env_path(*env, "PWD", 3);
	if (tmp && arg_path)
	{
		new_path = ft_strjoindelimit(tmp, "/", arg_path);
		update_env_var(env, "PWD", new_path);
		free(new_path);
	}
}

void	update_pwds(t_env **env, char *cur_dir, char *arg_path)
{
	char	*n_dir;

	set_oldpwd_env(env, cur_dir);
	n_dir = getcwd(NULL, 0);
	if (n_dir)
	{
		update_env_var(env, "PWD", n_dir);
		free(n_dir);
	}
	else
		recover_lost_pwd(env, arg_path);
}
