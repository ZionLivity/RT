/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/24 12:03:00 by rbenjami          #+#    #+#             */
/*   Updated: 2014/03/21 16:16:59 by rbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include "rt.h"

// void	option(t_scene *scene, char const *argv[])
// {
// 	if (argv[1][0] == '-')
// 	{
// 		if (ft_strchr(argv[1], 's'))
// 			scene->shadow = TRUE;
// 		if (ft_strchr(argv[1], 'b'))
// 			scene->brightness = TRUE;
// 	}
// 	else
// 		error("Usage :\n", "./rtv1 <-sb> [file.rtf]", TRUE, FALSE);
// }

int		main(int argc, char const *argv[])
{
	t_scene		scene;
	t_env		env;

	if (argc < 2 || argc > 3)
		return (error("Usage :\n", "./rt <-sb> [file.rtf]", FALSE, FALSE));
	if (argc == 2)
		scene = parse((char *)argv[1]);
	else
	{
		scene = parse((char *)argv[2]);
		// option(&scene, argv);
	}
	render(&env, &scene);
	return (0);
}
