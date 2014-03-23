/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quaternion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/17 13:09:33 by rbenjami          #+#    #+#             */
/*   Updated: 2014/03/23 17:19:48 by rbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib3d.h"

t_quaternion	new_quaternion4f(float x, float y, float z, float w)
{
	t_quaternion	new_quaternion;

	new_quaternion.x = x;
	new_quaternion.y = y;
	new_quaternion.z = z;
	new_quaternion.w = w;
	return (new_quaternion);
}

t_quaternion	new_quaternion4vf(t_vector3f axis, float angle)
{
	t_quaternion	new_quaternion;
	float			sin_half_angle;
	float			cos_half_angle;

	sin_half_angle = (float)sin(to_radians(angle) / 2);
	cos_half_angle = (float)cos(to_radians(angle) / 2);
	new_quaternion.x = axis.x * sin_half_angle;
	new_quaternion.y = axis.y * sin_half_angle;
	new_quaternion.z = axis.z * sin_half_angle;
	new_quaternion.w = cos_half_angle;
	return (new_quaternion);
}

float			length4(t_quaternion q)
{
	return ((float)sqrt(q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w));
}

t_quaternion	normalized4(t_quaternion q)
{
	float	l;

	l = length4(q);
	return (new_quaternion4f(q.x / l, q.y / l, q.z / l, q.w / l));
}

t_quaternion	conjugate4(t_quaternion q)
{
	return (new_quaternion4f(-q.x, -q.y, -q.z, q.w));
}
