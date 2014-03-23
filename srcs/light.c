/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/23 17:13:33 by rbenjami          #+#    #+#             */
/*   Updated: 2014/03/23 20:23:06 by rbenjami         ###   ########.fr       */
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
	float		specular;
	float		dot;

	specular = 0;
	dot = dot3(normalized3(ray), normalized3(r));
	if (dot > 0)
		specular = pow(dot, 20) * ((float)obj.specular / 100) * (obj.reflec / 10);
	return (mul3f(proj.color, specular));
}

int			shadows(t_scene *s, t_obj *obj, t_vector3f ray_d, t_vector3f ray_o)
{
	float		t;
	float		t2;
	t_obj		*tmpobj;
	t_objl		*tmpl;
	t_vector3f	tmp[2];

	tmpl = s->objl;
	t = -1;
	tmpobj = NULL;
	ray_o = get_transforms(ray_o, new_vector3f(0, 0, 0), conjugate4(obj->rot));
	ray_d = get_transforms(ray_d, new_vector3f(0, 0, 0), conjugate4(obj->rot));
	while (tmpl)
	{
		tmp[0] = get_transforms(ray_o, inv3(tmpl->obj->pos), tmpl->obj->rot);
		tmp[1] = get_transforms(ray_d, new_vector3f(0, 0, 0), tmpl->obj->rot);
		t2 = s->tab_type[tmpl->obj->type](tmp[0], *tmpl->obj, tmp[1]);
		if (t2 > 0 && t < 1 && (t2 < t || t == -1))
		{
			tmpobj = tmpl->obj;
			t = t2;
		}
		tmpl = tmpl->next;
	}
	return ((tmpobj && 0 < t && t < 1 && tmpobj != obj));
}
