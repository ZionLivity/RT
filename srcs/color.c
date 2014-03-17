/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/12 11:16:03 by rbenjami          #+#    #+#             */
/*   Updated: 2014/02/24 13:52:03 by rbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_color		rgb(int r, int g, int b)
{
	t_color	color;

	color.red = (r > 255) ? -1 : r;
	color.red = (r < 0) ? 0 : color.red;
	color.red = (r > 127) ? color.red - 256 : color.red;
	color.green = (g > 255) ? -1 : g;
	color.green = (g < 0) ? 0 : color.green;
	color.green = (g > 127) ? color.green - 256 : color.green;
	color.blue = (b > 255) ? -1 : b;
	color.blue = (b < 0) ? 0 : color.blue;
	color.blue = (b > 127) ? color.blue - 256 : color.blue;
	return (color);
}
