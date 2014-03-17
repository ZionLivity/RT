/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/24 16:43:00 by rbenjami          #+#    #+#             */
/*   Updated: 2014/03/07 17:24:40 by rbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <libft.h>
#include "rt.h"

int		error(const char *s1, char *s2, int exit_bool, int details)
{
	ft_putstr_fd("rtv1: \033[31m", 2);
	if (!s2)
	{
		ft_putendl_fd(s1, 2);
		ft_putstr_fd("\033[m", 2);
	}
	else
	{
		ft_putstr_fd(s1, 2);
		ft_putstr_fd("\033[m", 2);
		ft_putendl_fd(s2, 2);
	}
	if (details)
	{
		ft_putstr_fd("details:\n\t", 2);
		perror(s2);
	}
	if (exit_bool)
		exit(0);
	return (-42);
}
