/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector2f_rotate.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/25 11:56:13 by rbenjami          #+#    #+#             */
/*   Updated: 2014/02/25 12:36:52 by rbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib3d.h"

t_vector2f	rotate2(t_vector2f vec, float angle)
{
	float		rad;
	float		c;
	float		s;

	rad = to_radians(angle);
	c = cos(rad);
	s = sin(rad);
	return (new_vector2f(vec.x * c - vec.y * s, vec.x * s + vec.y * c));
}
