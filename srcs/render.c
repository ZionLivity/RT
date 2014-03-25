/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/24 12:19:31 by rbenjami          #+#    #+#             */
/*   Updated: 2014/03/25 11:53:54 by rbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <libft.h>
#include "rt.h"

void	add_cam(t_obj **obj, t_vector3f ray_d, t_vector3f ray_o)
{
	t_camera	*cam;

	cam = NULL;
	if (!(*obj)->cam)
	{
		if (!(cam = (t_camera *)ft_memalloc(sizeof(t_camera))))
			return ;
		cam->pos = get_transforms(ray_o, inv3((*obj)->pos), conjugate4((*obj)->rot));
		cam->ray = get_transforms(ray_d, new_vector3f(0, 0, 0), conjugate4((*obj)->rot));
		(*obj)->cam = cam;
	}
	else
	{
		(*obj)->cam->pos = get_transforms(ray_o, inv3((*obj)->pos), conjugate4((*obj)->rot));
		(*obj)->cam->ray = get_transforms(ray_d, new_vector3f(0, 0, 0), conjugate4((*obj)->rot));
	}
}

t_obj	*inter(t_scene *scene, t_vector3f ray_d, t_vector3f ray_o, t_vector3f *inter)
{
	float		t;
	float		t2;
	t_objl		*tmpl;
	t_obj		*obj;

	tmpl = scene->objl;
	t = -1;
	obj = NULL;
	while (tmpl)
	{
		add_cam(&tmpl->obj, ray_d, ray_o);
		t2 = scene->tab_type[tmpl->obj->type](tmpl->obj->cam->pos, *tmpl->obj, tmpl->obj->cam->ray);
		if (t2 > 0 && (t2 < t || t == -1))
		{
			t = t2;
			obj = tmpl->obj;
		}
		tmpl = tmpl->next;
	}
	if (obj && t > 0)
	{
		*inter = mul3f(obj->cam->ray, t);
		*inter = get_transforms(*inter, new_vector3f(0, 0, 0), obj->rot);
		*inter = get_transforms(*inter, ray_o, new_quaternion4f(0, 0, 0, 1));
		return (obj);
	}
	return (NULL);
}

t_vector3f	get_reflected(t_vector3f light_vec, t_vector3f normal)
{
	float		dot;

	dot = dot3(normalized3(light_vec), normalized3(normal));
	return (sub3v(normalized3(light_vec), mul3f(normalized3(normal), 2 * dot)));
}

t_vector3f	get_normal(t_obj obj, t_vector3f inter)
{
	t_vector3f	pos;
	t_vector3f	i;
	float		tmp;

	pos = get_transforms(obj.pos, new_vector3f(0, 0, 0), conjugate4(obj.rot));
	i = get_transforms(inter, new_vector3f(0, 0, 0), conjugate4(obj.rot));
	if (obj.type == SPHERE)
		return (sub3v(inter, obj.pos));
	if (obj.type == CYLINDER)
		return (new_vector3f(i.x - pos.x, 0, i.z - pos.z));
	if (obj.type == PLAN)
		return (get_transforms(new_vector3f(0, 1, 0), new_vector3f(0, 0, 0), obj.rot));
	tmp = -i.y - pos.y * tan(rt(obj.diameter / 2));
	if (obj.type == CONE)
		return (new_vector3f(i.x - pos.x, tmp, i.z - pos.z));
	return (new_vector3f(0, 0, 0));
}

t_color		ray_trace(t_scene *scene, t_vector3f ray, t_camera cam)
{
	t_vector3f	i;
	t_obj		*obj;
	t_vector3f	v[4];
	t_projl		*tmp;

	tmp = scene->projl;
	if ((obj = inter(scene, ray, cam.pos, &i)))
	{
		v[COLOR] = mul3f(obj->color, AMBIENT);
		while (tmp)
		{
			v[LIGHT_VEC] = sub3v(tmp->proj->pos, i);
			if (!shadows(scene, obj, v[LIGHT_VEC], i))
			{
				v[NORMAL] = get_normal(*obj, i);
				v[REFLECTED] = get_reflected(v[LIGHT_VEC], v[NORMAL]);
				v[COLOR] = add3v(v[COLOR], diffuse(*tmp->proj, *obj, v[LIGHT_VEC], v[NORMAL]));
				v[COLOR] = add3v(v[COLOR], specular(*tmp->proj, *obj, sub3v(i, cam.pos), v[REFLECTED]));
			}
			tmp = tmp->next;
		}
		return (rgbv(v[COLOR]));
	}
	return (rgb(0, 0, 0));
}

int			fill_img(t_scene *scene, t_img *img, t_camera cam)
{
	char		*tmp;
	t_color		color;
	t_vector2f	p;

	p.y = 0;
	while (p.y < WIN_H)
	{
		p.x = 0;
		while (p.x < WIN_W)
		{
			cam.ray = new_vector3f(p.x - (WIN_W / 2), p.y - (WIN_H / 2), WIN_W);
			cam.ray = add3v(cam.ray, mul3f(cam.forward, 1000));
			color = ray_trace(scene, normalized3(cam.ray), cam);
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
	rotate_x(&scene->cam, scene->camera.rot.x);
	rotate_y(&scene->cam, scene->camera.rot.y);
	fill_img(scene, &env->screen, scene->cam);
	env->scene = scene;
	env->cam = scene->cam;
	mlx_put_image_to_window(env->mlx, env->win, env->screen.img, 0, 0);
	mlx_expose_hook(env->win, expose_hook, env);
	mlx_key_hook(env->win, key_hook, env);
	mlx_loop(env->mlx);
	return (0);
}
