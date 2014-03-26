/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/24 16:40:11 by rbenjami          #+#    #+#             */
/*   Updated: 2014/03/26 15:34:03 by rbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <libft.h>
#include "rt.h"
#include "get_next_line.h"

static int		open_file(char *file)
{
	int		fd;
	char	*tmp;

	if (!(tmp = ft_strrchr(file, '.')))
		return (error(TRUE, "empty file extension: %s\n", file));
	if (ft_strcmp(tmp, ".rtf"))
		return (error(TRUE, "invalid file extension: %s\n", file));
	if ((fd = open(file, O_RDONLY)) == -1)
	{
		close(fd);
		return (error(TRUE, "open: %s\n", file));
	}
	return (fd);
}

void			fill_obj(t_parse *obj, int *nb_line, char *line)
{
	t_line	l;

	check_clean_line(&l, nb_line, line);
	obj->pos_x = (!ft_strcmp(l.var, "x")) ? l.value : obj->pos_x;
	obj->pos_y = (!ft_strcmp(l.var, "y")) ? l.value : obj->pos_y;
	obj->pos_z = (!ft_strcmp(l.var, "z")) ? l.value : obj->pos_z;
	obj->rot_x = (!ft_strcmp(l.var, "rot_x")) ? l.value : obj->rot_x;
	obj->rot_y = (!ft_strcmp(l.var, "rot_y")) ? l.value : obj->rot_y;
	obj->rot_z = (!ft_strcmp(l.var, "rot_z")) ? l.value : obj->rot_z;
	obj->red = (!ft_strcmp(l.var, "red")) ? l.value : obj->red;
	obj->green = (!ft_strcmp(l.var, "green")) ? l.value : obj->green;
	obj->blue = (!ft_strcmp(l.var, "blue")) ? l.value : obj->blue;
	obj->intens = (!ft_strcmp(l.var, "intensity")) ? l.value : obj->intens;
	obj->diameter = (!ft_strcmp(l.var, "diameter")) ? l.value : obj->diameter;
	obj->diffuse = (!ft_strcmp(l.var, "diffuse")) ? l.value : obj->diffuse;
	obj->specular = (!ft_strcmp(l.var, "specular")) ? l.value : obj->specular;
	obj->reflec = (!ft_strcmp(l.var, "reflection")) ? l.value : obj->reflec;
	obj->refrac = (!ft_strcmp(l.var, "refraction")) ? l.value : obj->refrac;
}

t_obj			*fill(t_scene *scene, int fd, int *nb_line, int type)
{
	char	*line;
	int		i;
	t_parse	obj;

	i = 0;
	init_obj(&obj);
	while (get_next_line(fd, &line) > 0)
	{
		if (ft_strcmp(line, "{") && !i)
			error(TRUE, "error: %d\n", *nb_line);
		if (!ft_strcmp(line, "}"))
		{
			ft_strdel(&line);
			break ;
		}
		else if (i)
			fill_obj(&obj, nb_line, line);
		i++;
		ft_strdel(&line);
	}
	*nb_line = *nb_line + 2;
	return (initobj(scene, &obj, type));
}

int				find_obj(t_scene *s, int fd, char *l, int *nl)
{
	if (!ft_strcmp(l, "#camera"))
		s->camera = fill(s, fd, nl, CAM);
	else if (!ft_strcmp(l, "#proj"))
		fill(s, fd, nl, PROJ);
	else if (!ft_strcmp(l, ".sphere"))
		fill(s, fd, nl, SPHERE);
	else if (!ft_strcmp(l, ".plan"))
		fill(s, fd, nl, PLAN);
	else if (!ft_strcmp(l, ".cylinder"))
		fill(s, fd, nl, CYLINDER);
	else if (!ft_strcmp(l, ".cone"))
		fill(s, fd, nl, CONE);
	else if (l[0] != '\0')
		return (error(TRUE, "object error line: %d\n", *nl));
	else
		return (0);
	*nl = *nl + 2;
	return (1);
}

t_scene			parse(char *file)
{
	int		fd;
	char	*line;
	t_scene	scene;
	int		nb_line;

	nb_line = 1;
	scene.objl = NULL;
	scene.cam = NULL;
	scene.camera = NULL;
	init_type(&scene.tab_type);
	scene.count_obj = 0;
	if (!(fd = open_file(file)))
		return (scene);
	while (get_next_line(fd, &line) > 0)
	{
		scene.count_obj++;
		ft_strtolower(line);
		if (!find_obj(&scene, fd, line, &nb_line))
			scene.count_obj--;
		ft_strdel(&line);
	}
	verify_scene(scene);
	return (scene);
}
