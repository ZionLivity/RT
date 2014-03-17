/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/14 20:33:20 by rbenjami          #+#    #+#             */
/*   Updated: 2014/02/24 12:06:08 by rbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include "rt.h"

void			check_clean_line(t_line *l, int *nb_line, char *line)
{
	int		i;
	int		lenth;

	i = 0;
	lenth = 0;
	ft_strtolower(line);
	while (line[i] == SPACE_CHAR || line[i] == TAB_CHAR)
		i++;
	while (line[i] != ':')
	{
		if (line[i] == '\0')
			error("error: separator, line: ", ft_itoa(*nb_line), TRUE, FALSE);
		l->var[lenth] = line[i];
		lenth++;
		i++;
	}
	l->var[lenth] = '\0';
	while (!ft_isdigit(line[i]) && line[i] != '-' && line[i] != '\0')
		i++;
	if (ft_isdigit(line[i]) || line[i] == '-')
		l->value = ft_atoi(&line[i]);
	else
		error("error: value, line: ", ft_itoa(*nb_line), TRUE, FALSE);
	*nb_line = *nb_line + 1;
}
