/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/12 11:16:03 by rbenjami          #+#    #+#             */
/*   Updated: 2014/03/18 14:40:44 by rbenjami         ###   ########.fr       */
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

t_color		rgbv(t_vector3f vec)
{
	t_color	color;

	color.red = (vec.x > 255) ? -1 : vec.x;
	color.red = (vec.x < 0) ? 0 : color.red;
	color.red = (vec.x > 127) ? color.red - 256 : color.red;
	color.green = (vec.y > 255) ? -1 : vec.y;
	color.green = (vec.y < 0) ? 0 : color.green;
	color.green = (vec.y > 127) ? color.green - 256 : color.green;
	color.blue = (vec.z > 255) ? -1 : vec.z;
	color.blue = (vec.z < 0) ? 0 : color.blue;
	color.blue = (vec.z > 127) ? color.blue - 256 : color.blue;
	return (color);
}
