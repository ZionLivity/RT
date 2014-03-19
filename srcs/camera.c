/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/24 15:17:59 by rbenjami          #+#    #+#             */
/*   Updated: 2014/03/19 16:39:04 by rbenjami         ###   ########.fr       */
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
	angle = to_radians(angle);
	cam->forward = rotate3(cam->forward, new_vector3f(1, 0, 0), angle);
	cam->up = rotate3(cam->up, new_vector3f(1, 0, 0), angle);
	cam->right = rotate3(cam->right, new_vector3f(1, 0, 0), angle);
}

void		rotate_y(t_camera *cam, float angle)
{
	angle = to_radians(angle);
	cam->forward = rotate3(cam->forward, new_vector3f(0, 1, 0), angle);
	cam->up = rotate3(cam->up, new_vector3f(0, 1, 0), angle);
	cam->right = rotate3(cam->right, new_vector3f(0, 1, 0), angle);
}

void		rotate_z(t_camera *cam, float angle)
{
	angle = to_radians(angle);
	cam->forward = rotate3(cam->forward, new_vector3f(0, 0, 1), angle);
	cam->up = rotate3(cam->up, new_vector3f(0, 0, 1), angle);
	cam->right = rotate3(cam->right, new_vector3f(0, 0, 1), angle);
}
