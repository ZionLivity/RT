/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix4f.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/24 15:19:24 by rbenjami          #+#    #+#             */
/*   Updated: 2014/03/17 18:44:08 by rbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib3d.h"

t_matrix4f		new_matrix4()
{
	t_matrix4f	res;

	res.m[0][0] = 1;
	res.m[0][1] = 0;
	res.m[0][2] = 0;
	res.m[0][3] = 0;

	res.m[1][0] = 0;
	res.m[1][1] = 1;
	res.m[1][2] = 0;
	res.m[1][3] = 0;

	res.m[2][0] = 0;
	res.m[2][1] = 0;
	res.m[2][2] = 1;
	res.m[2][3] = 0;

	res.m[3][0] = 0;
	res.m[3][1] = 0;
	res.m[3][2] = 0;
	res.m[3][3] = 1;
	return (res);
}

t_matrix4f		mul4m(t_matrix4f m, t_matrix4f r)
{
	t_matrix4f	res;
	int			i;
	int			j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			res.m[i][j] =	m.m[i][0] * r.m[0][j] +
							m.m[i][1] * r.m[1][j] +
							m.m[i][2] * r.m[2][j] +
							m.m[i][3] * r.m[3][j];
			j++;
		}
		i++;
	}
	return (res);
}

t_matrix4f		init_rotation3f(float x, float y, float z)
{
	t_matrix4f	rx;
	t_matrix4f	ry;
	t_matrix4f	rz;
	t_matrix4f	res;

	x = to_radians(x);
	y = to_radians(y);
	z = to_radians(z);

	rz.m[0][0] = (float)cos(z);		rz.m[0][1] = -(float)sin(z);	rz.m[0][2] = 0;					rz.m[0][3] = 0;
	rz.m[1][0] = (float)sin(z);		rz.m[1][1] = (float)cos(z);		rz.m[1][2] = 0;					rz.m[1][3] = 0;
	rz.m[2][0] = 0;					rz.m[2][1] = 0;					rz.m[2][2] = 1;					rz.m[2][3] = 0;
	rz.m[3][0] = 0;					rz.m[3][1] = 0;					rz.m[3][2] = 0;					rz.m[3][3] = 1;

	rx.m[0][0] = 1;					rx.m[0][1] = 0;					rx.m[0][2] = 0;					rx.m[0][3] = 0;
	rx.m[1][0] = 0;					rx.m[1][1] = (float)cos(x);		rx.m[1][2] = -(float)sin(x);	rx.m[1][3] = 0;
	rx.m[2][0] = 0;					rx.m[2][1] = (float)sin(x);		rx.m[2][2] = (float)cos(x);		rx.m[2][3] = 0;
	rx.m[3][0] = 0;					rx.m[3][1] = 0;					rx.m[3][2] = 0;					rx.m[3][3] = 1;

	ry.m[0][0] = (float)cos(y);		ry.m[0][1] = 0;					ry.m[0][2] = -(float)sin(y);	ry.m[0][3] = 0;
	ry.m[1][0] = 0;					ry.m[1][1] = 1;					ry.m[1][2] = 0;					ry.m[1][3] = 0;
	ry.m[2][0] = (float)sin(y);		ry.m[2][1] = 0;					ry.m[2][2] = (float)cos(y);		ry.m[2][3] = 0;
	ry.m[3][0] = 0;					ry.m[3][1] = 0;					ry.m[3][2] = 0;					ry.m[3][3] = 1;

	res = mul4m(rz, mul4m(ry, rx));
	return (res);
}

t_matrix4f		init_translation(float x, float y, float z)
{
	t_matrix4f	m;

	m.m[0][0] = 1;	m.m[0][1] = 0;	m.m[0][2] = 0;	m.m[0][3] = x;
	m.m[1][0] = 0;	m.m[1][1] = 1;	m.m[1][2] = 0;	m.m[1][3] = y;
	m.m[2][0] = 0;	m.m[2][1] = 0;	m.m[2][2] = 1;	m.m[2][3] = z;
	m.m[3][0] = 0;	m.m[3][1] = 0;	m.m[3][2] = 0;	m.m[3][3] = 1;

	return (m);
}

t_matrix4f		init_rotation3v(t_vector3f f, t_vector3f u, t_vector3f r)
{
	t_matrix4f	m;

	m.m[0][0] = r.x;	m.m[0][1] = r.y;	m.m[0][2] = r.z;	m.m[0][3] = 0;
	m.m[1][0] = u.x;	m.m[1][1] = u.y;	m.m[1][2] = u.z;	m.m[1][3] = 0;
	m.m[2][0] = f.x;	m.m[2][1] = f.y;	m.m[2][2] = f.z;	m.m[2][3] = 0;
	m.m[3][0] = 0;		m.m[3][1] = 0;		m.m[3][2] = 0;		m.m[3][3] = 1;
	return (m);
}

t_matrix4f		init_scale(float x, float y, float z)
{
	t_matrix4f	m;

	m.m[0][0] = x;	m.m[0][1] = 0;	m.m[0][2] = 0;	m.m[0][3] = 0;
	m.m[1][0] = 0;	m.m[1][1] = y;	m.m[1][2] = 0;	m.m[1][3] = 0;
	m.m[2][0] = 0;	m.m[2][1] = 0;	m.m[2][2] = z;	m.m[2][3] = 0;
	m.m[3][0] = 0;	m.m[3][1] = 0;	m.m[3][2] = 0;	m.m[3][3] = 1;
	return (m);
}

t_vector3f		transform(t_vector3f v, t_matrix4f m)
{
	float	x;
	float	y;
	float	z;

	x = m.m[0][0] * v.x + m.m[0][1] * v.y + m.m[0][2] * v.z + m.m[0][3];
	y = m.m[1][0] * v.x + m.m[1][1] * v.y + m.m[1][2] * v.z + m.m[1][3];
	z = m.m[2][0] * v.x + m.m[2][1] * v.y + m.m[2][2] * v.z + m.m[2][3];
	return (new_vector3f(x, y, z));
}
