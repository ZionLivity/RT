/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/25 14:48:54 by rbenjami          #+#    #+#             */
/*   Updated: 2014/03/19 18:10:42 by rbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

#include <stdio.h>

float		sphere(t_camera cam, t_obj sphere, t_vector3f ray)
{
	float	a;
	float	b;
	float	c;
	t_vector3f	ray_origin;
	t_vector3f	ray_dir;

	ray_origin = cam.pos;
	ray_dir = ray;
	ray_origin = transform(ray_origin, to_rotation_matrix(sphere.rot));
	ray_origin = transform(ray_origin, init_translation(sphere.pos));
	ray_dir = transform(ray_dir, to_rotation_matrix(sphere.rot));
	a = get_value3(pow3f(ray_dir, 2));
	b = get_value3(mul3v(ray_dir, ray_origin)) * 2;
	c = get_value3(pow3f(ray_origin, 2)) - rt(sphere.diameter / 2);
	return (res(a, b, c));
}

// t_matrix4f	get_transformation(t_transform t)
// {
// 	// t_matrix4f	translation_matrix;
// 	t_matrix4f	rotation_matrix;
// 	// t_matrix4f	scale_matrix;

// 	// translation_matrix = init_translation(t.pos);
// 	rotation_matrix = to_rotation_matrix(t.rot);
// 	// scale_matrix = init_scale(5, 5, 5);

// 	// return (mul4m(translation_matrix, rotation_matrix));
// 	return (rotation_matrix);
// }

float		cylinder(t_camera cam, t_obj cylinder, t_vector3f ray)
{
	float		a;
	float		b;
	float		c;
	t_vector3f	ray_origin;
	t_vector3f	ray_dir;
	t_vector2f	tmp[2];

	ray_origin = cam.pos;
	ray_dir = ray;
	ray_origin = transform(ray_origin, to_rotation_matrix(cylinder.rot));
	ray_origin = transform(ray_origin, init_translation(cylinder.pos));
	ray_dir = transform(ray_dir, to_rotation_matrix(cylinder.rot));
	tmp[0] = new_vector2f(ray_dir.x, ray_dir.z);
	tmp[1] = new_vector2f(ray_origin.x, ray_origin.z);
	a = get_value2(pow2f(tmp[0], 2));
	b = get_value2(mul2v(tmp[0], tmp[1])) * 2;
	c = get_value2(pow2f(tmp[1], 2)) - rt(cylinder.diameter / 2);
	return (res(a, b, c));
}

float		plan(t_camera cam, t_obj plan, t_vector3f ray)
{
	float		t;
	float		d;
	t_vector3f	norm;

	norm = new_vector3f(0, 1, 0);
	d = sqrt(rt(plan.pos.x) + rt(plan.pos.y) + rt(plan.pos.z));
	t = norm.x * (cam.pos.x - plan.pos.x);
	t += norm.y * (cam.pos.y - plan.pos.y);
	t += norm.z * (cam.pos.z - plan.pos.z) - 10;
	t /= norm.x * ray.x + norm.y * ray.y + norm.z * ray.z;
	return (t);
}
