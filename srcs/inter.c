/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/26 11:33:36 by rbenjami          #+#    #+#             */
/*   Updated: 2014/03/26 13:50:35 by rbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include "rt.h"

void	add_cam(t_obj **obj, t_vector3f ray_d, t_vector3f ray_o)
{
	t_camera		*cam;
	t_quaternion	q;

	cam = NULL;
	q = conjugate4((*obj)->rot);
	if (!(*obj)->cam)
	{
		if (!(cam = (t_camera *)ft_memalloc(sizeof(t_camera))))
			return ;
		cam->pos = get_transforms(ray_o, inv3((*obj)->pos), q);
		cam->ray = get_transforms(ray_d, new_vector3f(0, 0, 0), q);
		(*obj)->cam = cam;
	}
	else
	{
		(*obj)->cam->pos = get_transforms(ray_o, inv3((*obj)->pos), q);
		(*obj)->cam->ray = get_transforms(ray_d, new_vector3f(0, 0, 0), q);
	}
}

t_obj	*get_inter(t_obj *obj, float t, t_vector3f *inter, t_vector3f ray_o)
{
	if (obj && t > 0)
	{
		*inter = mul3f(obj->cam->ray, t);
		*inter = get_transforms(*inter, new_vector3f(0, 0, 0), obj->rot);
		*inter = get_transforms(*inter, ray_o, new_quaternion4f(0, 0, 0, 1));
		return (obj);
	}
	return (NULL);
}

t_obj	*inter(t_scene *s, t_vector3f ray_d, t_vector3f ray_o, t_vector3f *i)
{
	float		t;
	float		t2;
	t_objl		*tmpl;
	t_obj		*obj;
	t_vector3f	tmp[2];

	tmpl = s->objl;
	t = -1;
	obj = NULL;
	while (tmpl)
	{
		add_cam(&tmpl->obj, ray_d, ray_o);
		tmp[0] = tmpl->obj->cam->pos;
		tmp[1] = tmpl->obj->cam->ray;
		t2 = s->tab_type[tmpl->obj->type](tmp[0], *tmpl->obj, tmp[1]);
		if (t2 > 0 && (t2 < t || t == -1))
		{
			t = t2;
			obj = tmpl->obj;
		}
		tmpl = tmpl->next;
	}
	return (get_inter(obj, t, i, ray_o));
}

t_obj	*inter2(t_scene *scene, t_vector3f d, t_vector3f o)
{
	float		t;
	float		t2;
	t_objl		*l;
	t_obj		*obj;
	t_vector3f	tmp[2];

	l = scene->objl;
	t = -1;
	obj = NULL;
	while (l)
	{
		tmp[0] = get_transforms(o, inv3(l->obj->pos), conjugate4(l->obj->rot));
		tmp[1] = get_transforms(d, rgb(0, 0, 0), conjugate4(l->obj->rot));
		t2 = scene->tab_type[l->obj->type](tmp[0], *l->obj, tmp[1]);
		if (t2 > 0 && (t2 < t || t == -1))
		{
			t = t2;
			obj = l->obj;
		}
		l = l->next;
	}
	if (obj && t > 0)
		return (obj);
	return (NULL);
}
