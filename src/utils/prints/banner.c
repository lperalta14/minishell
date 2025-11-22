/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   banner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperalta <lperalta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 17:19:52 by lperalta          #+#    #+#             */
/*   Updated: 2025/11/21 20:08:52 by lperalta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

/**
 * @brief "Escribir el comentarioen ingles explicando que imprime un mensaje en codigo ascii"
 * 
 * @ingoup "rellenar el grupo"
 */
void	open_banner(void)
{
printf("%s", RED);
printf("          _____    __ _____  __          __  __    __  \n");
printf("%s", ORANGE);
printf("  /\\/\\    \\_   \\/\\ \\ \\\\_   \\/ _\\  /\\  /\\/__\\/ /   / /  \n");
printf("%s", YELLOW);
printf(" /    \\    / /\\/  \\/ / / /\\/\\ \\  / /_/ /_\\ / /   / /   \n");
printf("%s", GREEN);
printf("/ /\\/\\ \\/\\/ /_/ /\\  /\\/ /_  _\\ \\/ __  //__/ /___/ /___ \n");
printf("%s", BLUE);
printf("\\/    \\/\\____/\\_\\ \\/\\____/  \\__/\\/ /_/\\__/\\____/\\____/ \n");
printf("%s", PURPLE);
printf("                                                       \n");
printf("%s", NC);
}
/*
          _____    __ _____  __          __  __    __  
  /\\/\\    \\_   \\/\\ \\ \\\\_   \\/ _\\  /\\  /\\/__\\/ /   / /  
 /    \\    / /\\/  \\/ / / /\\/\\ \\  / /_/ /_\\ / /   / /   
/ /\\/\\ \\/\\/ /_/ /\\  /\\/ /_  _\\ \\/ __  //__/ /___/ /___ 
\\/    \\/\\____/\\_\\ \\/\\____/  \\__/\\/ /_/\\__/\\____/\\____/ 
                                                       
*/

/**
 * @brief "crear comentario en ingles explicando que la funcion abre un txt donde hay un banner en codigo ascii y lo imprime repitiendo 6 colores"
 * 
 * @param text, path of txt 
 */
void	print_banner(char *text)
{
	int	i;
	int	fd;
	char	*line;
	char	*color[6];

	color[0] = RED;
	color[1] = ORANGE;
	color[2] = YELLOW;
	color[3] = GREEN;
	color[4] = BLUE;
	color[5] = PURPLE;
	fd = open(text, O_RDONLY);
	i = 0;
	line = get_next_line(fd);
	while (line )
	{
		printf("%s%s", color[i % 6], line);
		free(line);
		line = get_next_line(fd);
		i++;
	}
	printf("%s\n", NC);
	close(fd);
}
