/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/25 14:48:54 by rbenjami          #+#    #+#             */
/*   Updated: 2014/03/17 18:56:17 by rbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

float		sphere(t_camera cam, t_obj sphere, t_vector3f ray)
{
	float	a;
	float	b;
	float	c;

	a = get_value3(pow3f(ray, 2));
	b = get_value3(mul3v(ray, sub3v(cam.pos, sphere.tran.pos))) * 2;
	c = get_value3(pow3f(sub3v(cam.pos, sphere.tran.pos), 2)) - rt(sphere.diameter / 2);
	return (res(a, b, c));
}

// t_matrix4f	get_transformation(t_transform t)
// {
// 	t_matrix4f	translation_matrix;
// 	t_matrix4f	rotation_matrix;
// 	t_matrix4f	scale_matrix;

// 	translation_matrix = init_translation(t.pos.x, t.pos.y, t.pos.z);
// 	rotation_matrix = to_rotation_matrix(t.rot);
// 	scale_matrix = init_scale(5, 5, 5);

// 	return mul4m(translation_matrix, mul4m(rotation_matrix, scale_matrix));
// }

float		cylinder(t_camera cam, t_obj cylinder, t_vector3f ray)
{
	float		a;
	float		b;
	float		c;
	t_vector2f	tmp[3];
	t_vector3f	tmp_ray;

	tmp_ray = transform(ray, to_rotation_matrix(cylinder.tran.rot));
	tmp[0] = new_vector2f(tmp_ray.x, tmp_ray.z);
	tmp[1] = new_vector2f(cam.pos.x, cam.pos.z);
	tmp[2] = new_vector2f(cylinder.tran.pos.x, cylinder.tran.pos.z);
	a = get_value2(pow2f(tmp[0], 2));
	b = get_value2(mul2v(tmp[0], sub2v(tmp[1], tmp[2]))) * 2;
	c = get_value2(pow2f(sub2v(tmp[1], tmp[2]), 2)) - rt(cylinder.diameter / 2);
	return (res(a, b, c));
}
