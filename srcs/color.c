/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/12 11:16:03 by rbenjami          #+#    #+#             */
/*   Updated: 2014/03/26 12:09:41 by rbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_vector3f	rgb(int r, int g, int b)
{
	t_vector3f	color;

	color.x = (r > 255) ? -1 : r;
	color.x = (r < 0) ? 0 : color.x;
	color.x = (r > 127) ? color.x - 256 : color.x;
	color.y = (g > 255) ? -1 : g;
	color.y = (g < 0) ? 0 : color.y;
	color.y = (g > 127) ? color.y - 256 : color.y;
	color.z = (b > 255) ? -1 : b;
	color.z = (b < 0) ? 0 : color.z;
	color.z = (b > 127) ? color.z - 256 : color.z;
	return (color);
}

t_vector3f	rgbv(t_vector3f vec)
{
	t_vector3f	color;

	color.x = (vec.x > 255) ? -1 : vec.x;
	color.x = (vec.x < 0) ? 0 : color.x;
	color.x = (vec.x > 127) ? color.x - 256 : color.x;
	color.y = (vec.y > 255) ? -1 : vec.y;
	color.y = (vec.y < 0) ? 0 : color.y;
	color.y = (vec.y > 127) ? color.y - 256 : color.y;
	color.z = (vec.z > 255) ? -1 : vec.z;
	color.z = (vec.z < 0) ? 0 : color.z;
	color.z = (vec.z > 127) ? color.z - 256 : color.z;
	return (color);
}
