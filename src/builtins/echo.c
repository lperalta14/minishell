/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msedeno- <msedeno-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 20:15:14 by msedeno-          #+#    #+#             */
/*   Updated: 2026/01/22 20:15:15 by msedeno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	ft_print_echo(char **args, int i)
{
	ft_putstr_fd(args[i], 1);
	if (args[i + 1])
		ft_putchar_fd(' ', 1);
}

int	ft_echo(char **args)
{
	int		i;
	size_t	j;
	int		newline;

	i = 1;
	newline = 1;
	while (args[i] && ft_strncmp(args[i], "-n", 2) == 0)
	{
		j = 2;
		while (args[i][j] && args[i][j] == 'n')
			j++;
		if (ft_strlen(args[i]) == j)
			newline = 0;
		else
			break ;
		i++;
	} // Imprimir argumentos
	while (args[i])
	{
		ft_print_echo(args, i);
		i++;
	} // Imprimir salto de línea si corresponde
	if (newline)
		ft_putchar_fd('\n', 1);
	return (0);
}
