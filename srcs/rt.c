/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/24 12:03:00 by rbenjami          #+#    #+#             */
/*   Updated: 2014/03/26 17:23:06 by rbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include "rt.h"

int		main(int argc, char const *argv[])
{
	t_scene		scene;
	t_env		env;

	if (argc < 2 || argc > 3)
		return (error(FALSE, "Usage :\n./rt <-sb> [file.rtf]"));
	if (argc == 2)
		scene = parse((char *)argv[1]);
	else
		scene = parse((char *)argv[2]);
	render(&env, &scene);
	return (0);
}
