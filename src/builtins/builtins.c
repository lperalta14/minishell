#include "../../include/minishell.h"

int	is_builtin(char *cmd)
{
	if (!ft_strncmp(cmd, "echo", ft_strlen(cmd)))
		return (1);
	else if (!ft_strncmp(cmd, "cd", ft_strlen(cmd)))
		return (2);
	else if (!ft_strncmp(cmd, "env", ft_strlen(cmd)))
		return (3);
	else if (!ft_strncmp(cmd, "exit", ft_strlen(cmd)))
		return (4);
	else if (!ft_strncmp(cmd, "export", ft_strlen(cmd)))
		return (5);
	else if (!ft_strncmp(cmd, "pwd", ft_strlen(cmd)))
		return (6);
	else if (!ft_strncmp(cmd, "unset", ft_strlen(cmd)))
		return (7);
	return (0);
}

int	execute_builtin(t_command *cmd, t_env **env)
{
	int	built;

	built = is_builtin(cmd->args[0]);
	if (!built || !env)
		return (0);
	if (built == 1)
		return (ft_echo(cmd->args));
	// else if (built == 2)
	// 	return (ft_cd(cmd->args));
	 else if (built == 3)
	 	return (ft_env(cmd->args));
	// else if (built == 4)
	// 	return (ft_exit(cmd->args));
	// else if (built == 5)
	// 	return (ft_export(cmd->args));
	else
	if (built == 6)
		return (ft_pwd());
	//else if (built == 7)
	//	return (ft_unset(cmd->args));
	return (0);
}
