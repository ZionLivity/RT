/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/24 15:17:59 by rbenjami          #+#    #+#             */
/*   Updated: 2014/03/17 14:40:15 by rbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_camera	new_camera(t_vector3f pos)
{
	t_camera	cam;

	cam.pos = pos;
	cam.forward = normalized3(new_vector3f(0, 0, 1));
	cam.up = normalized3(new_vector3f(0, 1, 0));
	cam.right = normalized3(new_vector3f(1, 0, 0));
	return (cam);
}

void		move(t_camera *cam, t_vector3f dir, float amt)
{
	cam->pos = add3v(cam->pos, mul3f(dir, amt));
}

void		rotate_x(t_camera *cam, float angle)
{
	t_vector3f	h_axis;
	t_vector3f	y_axis;

	y_axis = new_vector3f(0, 1, 0);
	h_axis = normalized3(cross3(y_axis, cam->forward));
	cam->forward = normalized3(rotate3(cam->forward, h_axis, to_radians(angle)));
	cam->up = normalized3(cross3(cam->forward, h_axis));
}

void		rotate_y(t_camera *cam, float angle)
{
	t_vector3f	h_axis;
	t_vector3f	y_axis;

	y_axis = new_vector3f(0, 1, 0);
	h_axis = normalized3(cross3(y_axis, cam->forward));
	cam->forward = normalized3(rotate3(cam->forward, y_axis, to_radians(angle)));
	cam->up = normalized3(cross3(cam->forward, h_axis));
}

