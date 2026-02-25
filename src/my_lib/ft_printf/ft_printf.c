/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msedeno- <msedeno-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 13:04:27 by lperalta          #+#    #+#             */
/*   Updated: 2025/12/16 17:35:01 by msedeno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int	ft_specifiers(char type, va_list args)
{
	int		cnt;

	cnt = 0;
	if (type == 'c')
		cnt += ft_putchar(va_arg(args, int));
	else if (type == 's')
		cnt += ft_putstr(va_arg(args, char *));
	else if (type == 'p')
		cnt += ft_putptr(va_arg(args, unsigned long));
	else if ((type == 'd' || type == 'i'))
		cnt += ft_putnbrcnt(va_arg(args, int));
	else if (type == 'u')
		cnt += ft_unsigput(va_arg(args, unsigned int));
	else if ((type == 'x') || (type == 'X'))
		cnt += ft_puthex(va_arg(args, unsigned int), type);
	else if (type == '%')
		cnt += ft_putchar('%');
	return (cnt);
}

int	ft_printf(const char *nbr, ...)
{
	va_list	args;
	int		count;

	count = 0;
	va_start(args, nbr);
	while (*nbr)
	{
		if (*nbr == '%')
		{
			nbr++;
			count += ft_specifiers(*nbr, args);
		}
		else
			count += (int) write(1, &nbr[0], 1);
		nbr ++;
	}
	va_end(args);
	return (count);
}
