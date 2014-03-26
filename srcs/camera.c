/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/24 15:17:59 by rbenjami          #+#    #+#             */
/*   Updated: 2014/03/26 15:24:28 by rbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include "rt.h"

t_camera	*new_camera(t_obj *camera)
{
	t_camera	*cam;

	if (!(cam = (t_camera *)ft_memalloc(sizeof(t_camera))))
		return (NULL);
	cam->pos = camera->pos;
	cam->f = normalized3(new_vector3f(0, 0, 1));
	cam->u = normalized3(new_vector3f(0, 1, 0));
	cam->r = normalized3(new_vector3f(1, 0, 0));
	cam->f = get_transforms(cam->f, new_vector3f(0, 0, 0), camera->rot);
	cam->u = get_transforms(cam->u, new_vector3f(0, 0, 0), camera->rot);
	cam->r = get_transforms(cam->r, new_vector3f(0, 0, 0), camera->rot);
	return (cam);
}

void		move(t_camera *cam, t_vector3f dir, float amt)
{
	cam->pos = add3v(cam->pos, mul3f(dir, amt));
}

void		rotate_x(t_camera *cam, float angle)
{
	angle = to_radians(angle);
	cam->f = rotate3(cam->f, new_vector3f(1, 0, 0), angle);
	cam->u = rotate3(cam->u, new_vector3f(1, 0, 0), angle);
	cam->r = rotate3(cam->r, new_vector3f(1, 0, 0), angle);
}

void		rotate_y(t_camera *cam, float angle)
{
	angle = to_radians(angle);
	cam->f = rotate3(cam->f, new_vector3f(0, 1, 0), angle);
	cam->u = rotate3(cam->u, new_vector3f(0, 1, 0), angle);
	cam->r = rotate3(cam->r, new_vector3f(0, 1, 0), angle);
}

void		rotate_z(t_camera *cam, float angle)
{
	angle = to_radians(angle);
	cam->f = rotate3(cam->f, new_vector3f(0, 0, 1), angle);
	cam->u = rotate3(cam->u, new_vector3f(0, 0, 1), angle);
	cam->r = rotate3(cam->r, new_vector3f(0, 0, 1), angle);
}
