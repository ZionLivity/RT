/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/26 12:20:45 by rbenjami          #+#    #+#             */
/*   Updated: 2014/03/26 14:31:53 by rbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

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
	t_vector3f	tmpv;
	float		tmp;

	tmpv = new_vector3f(0, 0, 0);
	pos = get_transforms(obj.pos, tmpv, conjugate4(obj.rot));
	i = get_transforms(inter, tmpv, conjugate4(obj.rot));
	if (obj.type == SPHERE)
		return (sub3v(inter, obj.pos));
	if (obj.type == CYLINDER)
		return (new_vector3f(i.x - pos.x, 0, i.z - pos.z));
	if (obj.type == PLAN)
		return (get_transforms(new_vector3f(0, 1, 0), tmpv, obj.rot));
	tmp = -i.y - pos.y * tan(rt(obj.diameter / 2));
	if (obj.type == CONE)
		return (new_vector3f(i.x - pos.x, tmp, i.z - pos.z));
	return (tmpv);
}

t_vector3f	get_color(t_scene *s, t_obj proj, t_obj *obj, t_vector3f i)
{
	t_vector3f	v[6];
	float		coef;

	v[C] = new_vector3f(0, 0, 0);
	v[L] = sub3v(proj.pos, i);
	if (!shadows(s, obj, v[L], i))
	{
		coef = (float)obj->reflec / 100;
		v[N] = get_normal(*obj, i);
		v[R] = get_reflected(v[L], v[N]);
		v[D] = add3v(v[C], diffuse(proj, *obj, v[L], v[N]));
		v[C] = add3v(v[D], specular(proj, *obj, sub3v(i, s->cam->pos), v[R]));
		v[R] = get_reflected(sub3v(i, s->cam->pos), v[N]);
		v[R2] = reflection(s, obj, i, v[R]);
		if (!(!v[R2].x && !v[R2].y && !v[R2].z))
		{
			v[C] = sub3v(v[C], mul3f(v[D], coef * 2));
			v[C] = add3v(v[C], mul3f(v[R], coef * 2));
		}
		v[C] = add3v(v[C], mul3f(v[R2], coef));
	}
	return (v[C]);
}
