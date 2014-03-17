/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector2f.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/24 12:24:33 by rbenjami          #+#    #+#             */
/*   Updated: 2014/02/25 15:20:33 by rbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib3d.h"

t_vector2f	new_vector2f(float x, float y)
{
	t_vector2f vec;

	vec.x = x;
	vec.y = y;
	return (vec);
}

float		length2(t_vector2f vec)
{
	return ((float)sqrt(vec.x * vec.x + vec.y * vec.y));
}

float		dot2(t_vector2f vec1, t_vector2f vec2)
{
	return (vec1.x * vec2.x + vec1.y * vec2.y);
}

float		cross2(t_vector2f vec1, t_vector2f vec2)
{
	return (vec1.x * vec2.y - vec1.y * vec2.x);
}

t_vector2f	normalized2(t_vector2f vec)
{
	float	length = length2(vec);

	return (new_vector2f(vec.x / length, vec.y / length));
}
