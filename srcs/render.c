/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/24 12:19:31 by rbenjami          #+#    #+#             */
/*   Updated: 2014/03/21 18:37:22 by rbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <libft.h>
#include "rt.h"

#include <stdio.h>

t_obj	*inter(t_scene *scene, t_vector3f ray, t_vector3f pos, t_vector3f *inter)
{
	float		t;
	float		t2;
	t_vector3f	tmp;
	t_objl		*tmpl;
	t_obj		*obj;

	tmpl = scene->objl;
	t = -1;
	obj = NULL;
	while (tmpl)
	{
		t2 = scene->tab_type[tmpl->obj->type](pos, *tmpl->obj, ray);
		if (t2 > 0 && (t2 < t || t == -1))
		{
			t = t2;
			obj = tmpl->obj;
		}
		tmpl = tmpl->next;
	}
	if (obj && t > 0)
	{
		*inter = mul3f(ray, t);
		*inter = add3v(*inter, pos);
		*inter = sub3v(*inter, obj->pos);
		tmp = *inter;
		tmp = transform(tmp, init_translation(obj->pos));
		tmp = transform(tmp, to_rotation_matrix(obj->rot));
		*inter = tmp;
		return (obj);
	}
	return (NULL);
}

t_vector3f	diffuse(t_obj proj, t_obj obj, t_vector3f light_vec, t_vector3f normal)
{
	float		diffuse;
	float		dot;

	diffuse = 0;
	dot = dot3(normalized3(inv(light_vec)), normalized3(normal));
	if (dot > 0)
		diffuse = dot * ((float)obj.diffuse_cmp / 100);
	return (mul3f(proj.color, diffuse));
}

t_vector3f	specular(t_obj proj, t_obj obj, t_vector3f ray, t_vector3f reflected)
{
	float		specular;
	float		dot;

	specular = 0;
	dot = dot3(normalized3(inv(ray)), normalized3(inv(reflected)));
	if (dot > 0)
		specular = pow(dot, 20) * ((float)obj.specular_cmp / 100) * (obj.reflection / 10);
	return (mul3f(proj.color, specular));
}

t_vector3f	shadows(t_scene *scene, t_obj *obj, t_vector3f light_vec, t_vector3f i)
{
	t_vector3f	i2;
	t_obj		*o;

	if ((o = inter(scene, inv(light_vec), i, &i2)) != NULL)
	{
		if (o == obj)
			return (new_vector3f(0, 0, 0));
		return (new_vector3f(-20, -20, -20));
	}
	return (new_vector3f(0, 0, 0));
}

t_vector3f	get_normal(t_obj obj, t_vector3f inter)
{
	if (obj.type == SPHERE)
		return (sub3v(inter, obj.pos));
	if (obj.type == CYLINDER)
		return (new_vector3f(inter.x - obj.pos.x, 0, inter.z - obj.pos.z));
	if (obj.type == PLAN)
		return (new_vector3f(0, 1, 0));
	return (new_vector3f(0, 0, 0));
}

t_vector3f	get_light_vec(t_obj proj, t_vector3f inter)
{
	return (sub3v(inter, inv(proj.pos)));
}

t_vector3f	get_reflected(t_vector3f light_vec, t_vector3f normal)
{
	float		dot;

	dot = dot3(normalized3(inv(light_vec)), normalized3(normal));
	return (sub3v(normalized3(inv(light_vec)), mul3f(normalized3(normal), 2 * dot)));
}

t_color	ray_trace(t_scene *scene, t_vector3f ray, t_camera cam)
{
	t_vector3f	i;
	t_obj		*obj;
	t_vector3f	color;
	t_vector3f	normal;
	t_vector3f	light_vec;
	t_vector3f	reflected;
	t_projl		*tmp;

	tmp = scene->projl;
	if ((obj = inter(scene, ray, cam.pos, &i)))
	{
		color = mul3f(obj->color, AMBIENT);
		while (tmp)
		{
			normal = get_normal(*obj, i);
			light_vec = get_light_vec(*tmp->proj, i);
			reflected = get_reflected(light_vec, normal);
			color = add3v(color, diffuse(*tmp->proj, *obj, light_vec, normal));
			color = add3v(color, specular(*tmp->proj, *obj, ray, reflected));
			// color = add3v(color, shadows(scene, obj, light_vec, i));
			tmp = tmp->next;
		}
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
