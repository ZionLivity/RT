/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix4f.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/24 15:19:24 by rbenjami          #+#    #+#             */
/*   Updated: 2014/03/26 17:04:35 by rbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib3d.h"

t_matrix4f		new_matrix4(void)
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
			res.m[i][j] = m.m[i][0] * r.m[0][j] + \
							m.m[i][1] * r.m[1][j] + \
							m.m[i][2] * r.m[2][j] + \
							m.m[i][3] * r.m[3][j];
			j++;
		}
		i++;
	}
	return (res);
}

t_matrix4f		init_translation(t_vector3f vec)
{
	t_matrix4f	m;

	m.m[0][0] = 1;
	m.m[0][1] = 0;
	m.m[0][2] = 0;
	m.m[0][3] = vec.x;
	m.m[1][0] = 0;
	m.m[1][1] = 1;
	m.m[1][2] = 0;
	m.m[1][3] = vec.y;
	m.m[2][0] = 0;
	m.m[2][1] = 0;
	m.m[2][2] = 1;
	m.m[2][3] = vec.z;
	m.m[3][0] = 0;
	m.m[3][1] = 0;
	m.m[3][2] = 0;
	m.m[3][3] = 1;
	return (m);
}

t_matrix4f		init_scale(float x, float y, float z)
{
	t_matrix4f	m;

	m.m[0][0] = x;
	m.m[0][1] = 0;
	m.m[0][2] = 0;
	m.m[0][3] = 0;
	m.m[1][0] = 0;
	m.m[1][1] = y;
	m.m[1][2] = 0;
	m.m[1][3] = 0;
	m.m[2][0] = 0;
	m.m[2][1] = 0;
	m.m[2][2] = z;
	m.m[2][3] = 0;
	m.m[3][0] = 0;
	m.m[3][1] = 0;
	m.m[3][2] = 0;
	m.m[3][3] = 1;
	return (m);
}
