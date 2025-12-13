/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_freematrix.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msedeno- <msedeno-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 14:53:03 by lperalta          #+#    #+#             */
/*   Updated: 2025/12/11 16:56:27 by msedeno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_utils.h"

void	ft_freematrix(char **str)
{
	int	i;

	if (!str)
		return ;
	i = 0;
	while (str && str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
	str = NULL;
}
