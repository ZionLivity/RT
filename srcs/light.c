/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/23 17:13:33 by rbenjami          #+#    #+#             */
/*   Updated: 2014/03/26 13:51:09 by rbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include "rt.h"

t_vector3f	diffuse(t_obj proj, t_obj obj, t_vector3f light_vec, t_vector3f n)
{
	float		diffuse;
	float		dot;

	diffuse = 0;
	dot = dot3(normalized3(light_vec), normalized3(n));
	if (dot > 0)
		diffuse = dot * ((float)obj.diffuse / 100);
	return (mul3f(proj.color, diffuse));
}

t_vector3f	specular(t_obj proj, t_obj obj, t_vector3f ray, t_vector3f r)
{
	float		spec;
	float		dot;

	spec = 0;
	dot = dot3(normalized3(ray), normalized3(r));
	if (dot > 0)
		spec = pow(dot, 20) * ((float)obj.specular / 100) * (obj.reflec / 10);
	return (mul3f(proj.color, spec));
}

t_vector3f	transform_ray(t_vector3f v, t_objl l, int ray_pos)
{
	t_vector3f	tmp;

	tmp = v;
	if (ray_pos && l.obj->type != PLAN)
		tmp = get_transforms(v, inv3(l.obj->pos), conjugate4(l.obj->rot));
	if (!ray_pos && l.obj->type != PLAN)
		tmp = get_transforms(v, new_vector3f(0, 0, 0), conjugate4(l.obj->rot));
	return (tmp);
}

t_vector3f	reflection(t_scene *s, t_obj *o, t_vector3f pos, t_vector3f ray)
{
	t_obj		*obj;
	t_projl		*tmp;

	tmp = s->projl;
	obj = inter2(s, ray, pos);
	if (obj != NULL && obj != o && o->reflec)
		return (rgbv(mul3f(obj->color, AMBIENT)));
	return (new_vector3f(0, 0, 0));
}

int			shadows(t_scene *s, t_obj *obj, t_vector3f d, t_vector3f o)
{
	float		t[2];
	t_obj		*tmpobj;
	t_objl		*tmpl;
	t_vector3f	tmp1;
	t_vector3f	tmp2;

	tmpl = s->objl;
	t[0] = -1;
	tmpobj = NULL;
	while (tmpl)
	{
		tmp1 = transform_ray(o, *tmpl, 1);
		tmp2 = transform_ray(d, *tmpl, 0);
		t[1] = s->tab_type[tmpl->obj->type](tmp1, *tmpl->obj, tmp2);
		if (t[1] > 0 && t[0] < 1 && (t[1] < t[0] || t[0] == -1))
		{
			tmpobj = tmpl->obj;
			t[0] = t[1];
		}
		tmpl = tmpl->next;
	}
	return ((tmpobj && 0 < t[0] && t[0] < 1 && tmpobj != obj));
}
