/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/25 14:48:54 by rbenjami          #+#    #+#             */
/*   Updated: 2014/03/21 18:52:47 by rbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

#include <stdio.h>

float		sphere(t_vector3f pos, t_obj sphere, t_vector3f ray)
{
	float	a;
	float	b;
	float	c;
	t_vector3f	ray_origin;
	t_vector3f	ray_dir;

	ray_origin = pos;
	ray_dir = ray;
	ray_origin = transform(ray_origin, to_rotation_matrix(sphere.rot));
	ray_origin = transform(ray_origin, init_translation(inv(sphere.pos)));
	ray_dir = transform(ray_dir, to_rotation_matrix(sphere.rot));
	a = get_value3(pow3f(ray_dir, 2));
	b = get_value3(mul3v(ray_dir, ray_origin)) * 2;
	c = get_value3(pow3f(ray_origin, 2)) - rt(sphere.diameter / 2);
	return (res(a, b, c));
}

float		cylinder(t_vector3f pos, t_obj cylinder, t_vector3f ray)
{
	float		a;
	float		b;
	float		c;
	t_vector3f	ray_origin;
	t_vector3f	ray_dir;
	t_vector2f	tmp[2];

	ray_origin = pos;
	ray_dir = ray;
	ray_origin = transform(ray_origin, to_rotation_matrix(cylinder.rot));
	ray_origin = transform(ray_origin, init_translation(inv(cylinder.pos)));
	ray_dir = transform(ray_dir, to_rotation_matrix(cylinder.rot));
	tmp[0] = new_vector2f(ray_dir.x, ray_dir.z);
	tmp[1] = new_vector2f(ray_origin.x, ray_origin.z);
	a = get_value2(pow2f(tmp[0], 2));
	b = get_value2(mul2v(tmp[0], tmp[1])) * 2;
	c = get_value2(pow2f(tmp[1], 2)) - rt(cylinder.diameter / 2);
	return (res(a, b, c));
}

float		plan(t_vector3f pos, t_obj plan, t_vector3f ray)
{
	float		d;
	float		t;
	t_vector3f	norm;
	t_vector3f	ray_origin;
	t_vector3f	ray_dir;

	ray_origin = pos;
	ray_dir = ray;
	ray_origin = transform(ray_origin, to_rotation_matrix(plan.rot));
	ray_origin = transform(ray_origin, init_translation(inv(plan.pos)));
	ray_dir = transform(ray_dir, to_rotation_matrix(plan.rot));
	norm = normalized3(new_vector3f(0, 1, 0));
	d = length3(sub3v(plan.pos, pos));
	t = dot3(norm, normalized3(plan.pos)) - d;
	t /= dot3(norm, normalized3(ray_dir));
	return (t);
}
