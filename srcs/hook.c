/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/13 17:42:35 by rbenjami          #+#    #+#             */
/*   Updated: 2014/03/21 18:44:21 by rbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdlib.h>
#include <libft.h>
#include "rt.h"

int				expose_hook(t_env *e)
{
	mlx_put_image_to_window(e->mlx, e->win, e->screen.img, 0, 0);
	return (0);
}

static void		debug(t_env *e)
{
	char	*nbr;

	mlx_string_put(e->mlx, e->win, 10, 20, 0xFF0000, "x: ");
	nbr = ft_itoa(e->cam.pos.x);
	mlx_string_put(e->mlx, e->win, 25, 20, 0xFF0000, nbr);
	free(nbr);
	mlx_string_put(e->mlx, e->win, 10, 30, 0xFF0000, "y: ");
	nbr = ft_itoa(e->cam.pos.y);
	mlx_string_put(e->mlx, e->win, 25, 30, 0xFF0000, nbr);
	free(nbr);
	mlx_string_put(e->mlx, e->win, 10, 40, 0xFF0000, "z: ");
	nbr = ft_itoa(e->cam.pos.z);
	mlx_string_put(e->mlx, e->win, 25, 40, 0xFF0000, nbr);
	free(nbr);
}

int				key_hook(int keycode, t_env *e)
{
	if (keycode == 65307)
	{
		mlx_destroy_image(e->mlx, e->screen.img);
		mlx_destroy_window(e->mlx, e->win);
		exit(0);
	}
	else
	{
		// ft_putendl(ft_itoa(keycode));
		if (keycode == 65362)
			move(&e->cam, e->cam.forward, 100);
		if (keycode == 65364)
			move(&e->cam, e->cam.forward, -100);
		if (keycode == 65361)
			move(&e->cam, e->cam.right, -20);
		if (keycode == 65363)
			move(&e->cam, e->cam.right, 20);
		if (keycode == 32)
			move(&e->cam, e->cam.up, 20);
		if (keycode == 65505)
			move(&e->cam, e->cam.up, -20);
		if (keycode == 65464)
			rotate_x(&e->cam, 20);
		if (keycode == 65458)
			rotate_x(&e->cam, -20);
		if (keycode == 65457)
			rotate_y(&e->cam, -20);
		if (keycode == 65459)
			rotate_y(&e->cam, 20);
		if (keycode == 65460)
			rotate_z(&e->cam, 20);
		if (keycode == 65452)
			rotate_z(&e->cam, -20);
		fill_img(e->scene, &e->screen, e->cam);
		mlx_put_image_to_window(e->mlx, e->win, e->screen.img, 0, 0);
		debug(e);
	}
	return (0);
}
