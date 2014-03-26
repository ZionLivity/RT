/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/04 16:26:15 by rbenjami          #+#    #+#             */
/*   Updated: 2014/03/26 14:53:41 by rbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <libft.h>
#include "rt.h"

/*
**	Error:
**	%c -> char
**	%s -> char*
**	%d -> int
*/

int		ft_putcolored_char(char c, int color)
{
	if (color == BLACK)
		ft_putstr("\033[30m");
	if (color == RED)
		ft_putstr("\033[31m");
	if (color == GREEN)
		ft_putstr("\033[32m");
	if (color == YELLOW)
		ft_putstr("\033[33m");
	if (color == BLUE)
		ft_putstr("\033[34m");
	if (color == MAGENTA)
		ft_putstr("\033[35m");
	if (color == CYAN)
		ft_putstr("\033[36m");
	if (color == WITHE)
		ft_putstr("\033[37m");
	ft_putchar(c);
	ft_putstr("\033[m");
	return (1);
}

void	print_arg(char c, va_list ap)
{
	if (c == '%')
		ft_putchar_fd('%', 2);
	else if (c == 'c')
		ft_putchar_fd(va_arg(ap, int), 2);
	else if (c == 's')
		ft_putstr_fd(va_arg(ap, char*), 2);
	else if (c == 'd')
		ft_putnbr_fd(va_arg(ap, int), 2);
}

int		error(int quit, const char *msg, ...)
{
	va_list		ap;

	ft_putstr_fd("RT: ", 2);
	va_start(ap, msg);
	while (*msg)
	{
		if (*msg == '%')
		{
			msg++;
			print_arg(*msg, ap);
		}
		else
			ft_putcolored_char(*msg, 1);
		msg++;
	}
	va_end(ap);
	if (quit)
		exit(0);
	return (-42);
}
