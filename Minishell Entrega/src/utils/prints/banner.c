/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   banner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperalta <lperalta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 17:19:52 by lperalta          #+#    #+#             */
/*   Updated: 2026/01/23 14:45:16 by lperalta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

/**
 * @brief "crear comentario en ingles explicando que la funcion abre 
 * un txt donde hay un banner en codigo ascii y lo imprime repitiendo 6 colores"
 * 
 * @param text, path of txt 
 */
void	print_banner(char *text)
{
	int		i;
	int		fd;
	char	*line;
	char	*color[6];

	i = 0;
	color[0] = RED;
	color[1] = ORANGE;
	color[2] = YELLOW;
	color[3] = GREEN;
	color[4] = BLUE;
	color[5] = PURPLE;
	fd = open(text, O_RDONLY);
	if (fd < 0)
		return ;
	line = get_next_line(fd);
	while (line && ++i)
	{
		printf("%s%s", color[i % 6], line);
		free(line);
		line = get_next_line(fd);
	}
	printf("%s%s%s%s%s%s%s%s%s%s%s\n", RED, "by: ", ORANGE,
		"msed", GREEN, "eno- &", BLUE, "& lpera", PURPLE, "lta :)", NC);
	close(fd);
}
