/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector3f_rotate.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/24 16:19:46 by rbenjami          #+#    #+#             */
/*   Updated: 2014/03/17 13:32:03 by rbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib3d.h"

t_vector3f	rotate3(t_vector3f vec, t_vector3f axis, float angle)
{
	float 		sin_angle;
	float 		cos_angle;
	t_vector3f	tmp;

	sin_angle = (float)sin(-angle);
	cos_angle = (float)cos(-angle);
	tmp = cross3(vec, mul3f(axis, sin_angle));
	tmp = add3v(tmp, mul3f(vec, cos_angle));
	tmp = add3v(tmp, mul3f(vec, dot3(vec, mul3f(axis, 1 - cos_angle))));
	return (tmp);
}

t_vector3f	rotate3q(t_vector3f vec, t_quaternion rotation)
{
	t_quaternion	conjugate;
	t_quaternion	w;

	conjugate = conjugate4(rotation);
	w = mul4q(mul4v(rotation, vec), conjugate);
	return (new_vector3f(w.x, w.y, w.z));
}
