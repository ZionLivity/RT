/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/24 12:19:31 by rbenjami          #+#    #+#             */
/*   Updated: 2014/03/26 16:20:27 by rbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <libft.h>
#include "rt.h"

t_vector3f	ray_trace(t_scene *scene, t_vector3f ray, t_camera cam)
{
	t_vector3f	i;
	t_obj		*obj;
	t_vector3f	c;
	t_projl		*tmp;

	tmp = scene->projl;
	if ((obj = inter(scene, ray, cam.pos, &i)))
	{
		c = mul3f(obj->color, AMBIENT);
		while (tmp)
		{
			c = add3v(c, get_color(scene, *tmp->proj, obj, i));
			tmp = tmp->next;
		}
		return (rgbv(c));
	}
	return (rgb(0, 0, 0));
}

int			fill_img(t_scene *scene, t_img *img, t_camera cam)
{
	char		*tmp;
	t_vector3f	color;
	t_vector2f	p;

	p.y = 0;
	while (p.y < WIN_H)
	{
		p.x = 0;
		while (p.x < WIN_W)
		{
			cam.ray = new_vector3f(p.x - (WIN_W / 2), p.y - (WIN_H / 2), WIN_W);
			cam.ray = add3v(cam.ray, mul3f(cam.f, 1000));
			color = ray_trace(scene, normalized3(cam.ray), cam);
			tmp = &img->data[(int)((WIN_H - p.y) * img->sizeline + p.x * \
				(img->bpp / 8))];
			tmp[0] = color.z;
			tmp[1] = color.y;
			tmp[2] = color.x;
			p.x++;
		}
		p.y++;
	}
	return (1);
}

int			render(t_env *env, t_scene *scene)
{
	int			e;

	if ((env->mlx = mlx_init()) == NULL)
		return (error(FALSE, "mlx init error: \n"));
	if ((env->win = mlx_new_window(env->mlx, WIN_W, WIN_H, "RT")) == NULL)
		return (error(FALSE, "window error: \n"));
	env->screen.img = mlx_new_image(env->mlx, WIN_W, WIN_H);
	env->screen.data = mlx_get_data_addr(env->screen.img, &env->screen.bpp, \
												&env->screen.sizeline, &e);
	scene->cam = new_camera(scene->camera);
	rotate_x(scene->cam, scene->camera->rot.x);
	rotate_y(scene->cam, scene->camera->rot.y);
	fill_img(scene, &env->screen, *scene->cam);
	env->scene = scene;
	env->cam = *scene->cam;
	mlx_put_image_to_window(env->mlx, env->win, env->screen.img, 0, 0);
	mlx_expose_hook(env->win, expose_hook, env);
	mlx_key_hook(env->win, key_hook, env);
	mlx_loop(env->mlx);
	return (0);
}
