/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/26 10:54:29 by rbenjami          #+#    #+#             */
/*   Updated: 2014/03/26 14:13:44 by rbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include "rt.h"

void			init_type(t_find_type **tab_type)
{
	*tab_type = (t_find_type *)ft_memalloc(sizeof(t_find_type) * 4);
	(*tab_type)[0] = &sphere;
	(*tab_type)[1] = &cylinder;
	(*tab_type)[2] = &plan;
	(*tab_type)[3] = &cone;
}

void			add_obj(t_scene *scene, t_obj *obj)
{
	t_objl	*newl;
	t_objl	*tmp;

	if (!(newl = (t_objl *)ft_memalloc(sizeof(t_objl))))
		return ;
	newl->obj = obj;
	newl->next = NULL;
	if (!scene->objl)
		scene->objl = newl;
	else
	{
		tmp = scene->objl;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = newl;
	}
}

void			add_proj(t_scene *scene, t_obj *proj)
{
	t_projl	*newl;
	t_projl	*tmp;

	if (!(newl = (t_projl *)ft_memalloc(sizeof(t_projl))))
		return ;
	newl->proj = proj;
	newl->next = NULL;
	if (!scene->projl)
		scene->projl = newl;
	else
	{
		tmp = scene->projl;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = newl;
	}
}

t_obj			*initobj(t_scene *scene, t_parse *p, int type)
{
	t_obj		*obj;
	t_vector3f	v;

	if (!(obj = (t_obj *)ft_memalloc(sizeof(t_obj))))
		return (NULL);
	obj->rot = new_quaternion4vf(new_vector3f(1, 0, 0), p->rot_x);
	v = new_vector3f(0, 1, 0);
	obj->rot = mul4q(obj->rot, new_quaternion4vf(v, p->rot_y));
	v = new_vector3f(0, 0, 1);
	obj->rot = mul4q(obj->rot, new_quaternion4vf(v, p->rot_z));
	obj->pos = new_vector3f(p->pos_x, p->pos_y, p->pos_z);
	obj->color = new_vector3f(p->red, p->green, p->blue);
	obj->diameter = p->diameter;
	obj->intens = p->intens;
	obj->diffuse = p->diffuse;
	obj->specular = p->specular;
	obj->type = type;
	obj->refrac = p->refrac;
	obj->reflec = p->reflec;
	obj->cam = NULL;
	if (type >= 0)
		add_obj(scene, obj);
	else if (type == PROJ)
		add_proj(scene, obj);
	return (obj);
}

void			init_obj(t_parse *obj)
{
	obj->rot_x = 0;
	obj->rot_y = 0;
	obj->rot_z = 0;
	obj->pos_x = 0;
	obj->pos_y = 0;
	obj->pos_z = 0;
	obj->red = 0;
	obj->green = 0;
	obj->blue = 0;
	obj->diameter = 100;
	obj->intens = 100;
	obj->diffuse = 20;
	obj->specular = 20;
	obj->type = 0;
	obj->refrac = 0;
	obj->reflec = 0;
}
