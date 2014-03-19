/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/24 12:19:31 by rbenjami          #+#    #+#             */
/*   Updated: 2014/03/19 19:12:39 by rbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <libft.h>
#include "rt.h"

#include <stdio.h>

t_obj	*inter(t_scene *scene, t_vector3f ray, t_camera cam, t_vector3f *inter)
{
	float	t;
	t_vector3f	tmp;

	if ((t = sphere(cam, scene->sphere[0], ray)) > 0)
	{
		*inter = mul3f(ray, t);
		*inter = add3v(*inter, cam.pos);
		tmp = *inter;
		tmp = transform(tmp, init_translation(scene->sphere[0].pos));
		tmp = transform(tmp, to_rotation_matrix(scene->sphere[0].rot));
		*inter = tmp;
		return (&scene->sphere[0]);
	}
	// if ((t = cylinder(cam, scene->cylinder[0], ray)) > 0)
	// {
	// 	*inter = mul3f(ray, t);
	// 	*inter = add3v(*inter, cam.pos);
	// 	tmp = *inter;
	// 	tmp = transform(tmp, init_translation(scene->cylinder[0].pos));
	// 	tmp = transform(tmp, to_rotation_matrix(scene->cylinder[0].rot));
	// 	*inter = tmp;
	// 	return (&scene->cylinder[0]);
	// }
	return (NULL);
}
t_vector3f	light(t_obj proj, t_vector3f normal, t_vector3f ray, t_vector3f inter)
{
	t_vector3f	light_vec;
	t_vector3f	color;
	float		dot;

	(void)ray;
	light_vec = sub3v(inter, proj.pos);
	dot = dot3(normalized3(normal), normalized3(inv(light_vec)));
	if (dot <= 0)
		return (new_vector3f(0, 0, 0));
	else
	{
		color = mul3f(proj.color, dot);
		return (color);
	}
}
// t_vector3f	light(t_obj proj, t_vector3f N, t_vector3f V, t_vector3f inter)
// {
// 	t_vector3f	L;
// 	t_vector3f	diffuse;
// 	t_vector3f	spec;
// 	t_vector3f	R;
// 	float		dot;
// 	float		dot2;
// 	// float		intensity;
// 	// float		dist;

// 	L = sub3v(inter, proj.pos);
// 	dot = dot3(normalized3(L), normalized3(inv(N)));
// 	if (dot <= 0)
// 		return (new_vector3f(0, 0, 0));
// 	else
// 	{
// 		diffuse = mul3f(proj.color, dot);
// 		R = sub3v(inv(L), mul3f(N, dot * 2));
// 		dot2 = dot3(normalized3(V), normalized3(R));
// 		if (dot2 > 0)
// 		{
// 			printf("%f\n", dot2);
// 			spec = mul3f(proj.color, dot2);
// 		}
// 		else
// 			spec = new_vector3f(0, 0, 0);
// 		//intensity = diffuse * (L.N) + specular * (V.R)n
// 		// return (add3v(mul3f(diffuse, dot), mul3f(spec, dot2)));
// 		// return (mul3f(diffuse, dot));
// 		return (mul3f(spec, dot2));
// 	}
// 	return (new_vector3f(0, 0, 0));
// }

t_vector3f	get_normal(t_obj obj, t_vector3f inter)
{
	// t_vector3f	tmp;

	// tmp = inter;
	// tmp = transform(tmp, init_translation(obj.pos));
	// tmp = transform(tmp, to_rotation_matrix(obj.rot));
	if (obj.type == SPHERE)
		return (sub3v(inter, obj.pos));
	if (obj.type == CYLINDER)
		return (new_vector3f(inter.x - obj.pos.x, 0, inter.z - obj.pos.z));
	return (new_vector3f(0, 0, 0));
}

t_color	ray_trace(t_scene *scene, t_vector3f ray, t_camera cam)
{
	t_vector3f	i;
	t_obj		*obj;
	t_vector3f	color;
	int			j;

	j = 0;
	if ((obj = inter(scene, ray, cam, &i)))
	{
		color = mul3f(obj->color, 0.2);
		while (j < scene->elem.nb_proj)
			color = add3v(color, light(scene->proj[j++], get_normal(*obj, i), ray ,i));
		// printf("red: %f | green: %f | blue: %f\n", color.x, color.y, color.z);
		return (rgbv(color));
	}
	return (rgb(0, 0, 0));
}

int		fill_img(t_scene *scene, t_img *img, t_camera cam)
{
	char		*tmp;
	t_color		color;
	t_vector3f	ray;
	t_vector2f	p;

	p.y = 0;
	while (p.y < WIN_H)
	{
		p.x = 0;
		while (p.x < WIN_W)
		{
			ray = new_vector3f(p.x - (WIN_W / 2), p.y - (WIN_H / 2), WIN_W);
			ray = add3v(ray, mul3f(cam.forward, 1000));
			color = ray_trace(scene, normalized3(ray), cam);
			tmp = &img->data[(int)((WIN_H - p.y) * img->sizeline + p.x * (img->bpp / 8))];
			tmp[0] = color.blue;
			tmp[1] = color.green;
			tmp[2] = color.red;
			p.x++;
		}
		p.y++;
	}
	return (1);
}

int		render(t_env *env, t_scene *scene)
{
	int			e;

	if ((env->mlx = mlx_init()) == NULL)
		return (error("mlx init error: ", NULL, FALSE, TRUE));
	if ((env->win = mlx_new_window(env->mlx, WIN_W, WIN_H, "RT")) == NULL)
		return (error("window error: ", NULL, FALSE, TRUE));
	env->screen.img = mlx_new_image(env->mlx, WIN_W, WIN_H);
	env->screen.data = mlx_get_data_addr(env->screen.img, &env->screen.bpp, \
												&env->screen.sizeline, &e);
	scene->cam = new_camera(scene->camera.pos);
	rotate_x(&env->cam, scene->camera.rot.x);
	rotate_y(&env->cam, scene->camera.rot.y);
	fill_img(scene, &env->screen, scene->cam);
	env->scene = scene;
	env->cam = scene->cam;
	mlx_put_image_to_window(env->mlx, env->win, env->screen.img, 0, 0);
	mlx_expose_hook(env->win, expose_hook, env);
	mlx_key_hook(env->win, key_hook, env);
	mlx_loop(env->mlx);
	return (0);
}
