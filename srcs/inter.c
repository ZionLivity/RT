/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/25 14:48:54 by rbenjami          #+#    #+#             */
/*   Updated: 2014/03/24 17:08:15 by rbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

float		sphere(t_vector3f pos, t_obj sphere, t_vector3f ray)
{
	float	a;
	float	b;
	float	c;

	a = get_value3(rt3(ray));
	b = get_value3(mul3v(ray, pos)) * 2;
	c = get_value3(rt3(pos)) - rt(sphere.diameter / 2);
	return (res(a, b, c));
}

float		cylinder(t_vector3f pos, t_obj cylinder, t_vector3f ray)
{
	float		a;
	float		b;
	float		c;
	t_vector2f	tmp[2];

	tmp[0] = new_vector2f(ray.x, ray.z);
	tmp[1] = new_vector2f(pos.x, pos.z);
	a = get_value2(rt2(tmp[0]));
	b = get_value2(mul2v(tmp[0], tmp[1])) * 2;
	c = get_value2(rt2(tmp[1])) - rt(cylinder.diameter / 2);
	return (res(a, b, c));
}

float		plan(t_vector3f pos, t_obj plan, t_vector3f ray)
{
	float		d;

	(void)plan;
	if (fabs(ray.y) < 0.00001)
		return (-1);
	d = pos.y / ray.y;
	return (-d);
}

float		cone(t_vector3f pos, t_obj cone, t_vector3f ray)
{
	float	a;
	float	b;
	float	c;
	float	r;

	r = cone.diameter / 200;
	a = rt(ray.x) + rt(ray.z) - (rt(r) * rt(ray.y));
	b =	ray.x * pos.x;
	b += ray.z * pos.z;
	b -= ray.y * rt(r) * pos.y;
	b *= 2;
	c = rt(pos.x);
	c += rt(pos.z);
	c -= rt(r) * rt(pos.y);
	return (res(a, b, c));
}
