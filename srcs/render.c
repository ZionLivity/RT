/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/24 12:19:31 by rbenjami          #+#    #+#             */
/*   Updated: 2014/03/17 18:58:50 by rbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <libft.h>
#include "rt.h"


#include <stdio.h>
int		inter(t_scene *scene, t_vector3f ray, t_camera cam, t_vector3f *inter)
{
	float	t;

	// if ((t = sphere(cam, scene->sphere[0], ray)) != -1)
	// {
	// 	*inter = mul3f(ray, t);
	// 	return (1);
	// }
	if ((t = cylinder(cam, scene->cylinder[0], ray)) != -1)
	{
		*inter = mul3f(ray, t);
		return (1);
	}
	return (0);
}

t_color	ray_trace(t_scene *scene, t_vector3f ray, t_camera cam)
{
	t_vector3f	i;

	if (inter(scene, ray, cam, &i))
		return (rgb(0, 255, 0));
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
	env->cam = new_camera(scene->cam.tran.pos);
	rotate_x(&env->cam, scene->cam.tran.rot.x);
	rotate_y(&env->cam, scene->cam.tran.rot.y);
	fill_img(scene, &env->screen, env->cam);
	env->scene = scene;
	mlx_put_image_to_window(env->mlx, env->win, env->screen.img, 0, 0);
	mlx_expose_hook(env->win, expose_hook, env);
	mlx_key_hook(env->win, key_hook, env);
	mlx_loop(env->mlx);
	return (0);
}
