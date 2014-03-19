/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/24 16:40:11 by rbenjami          #+#    #+#             */
/*   Updated: 2014/03/19 14:37:06 by rbenjami         ###   ########.fr       */
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
		return (error("empty file extension: ", file , TRUE, FALSE));
	if (ft_strcmp(tmp, ".rtf"))
		return (error("invalid file extension: ", file , TRUE, FALSE));
	if ((fd = open(file, O_RDONLY)) == -1)
	{
		close(fd);
		return (error("open: ", file, TRUE, TRUE));
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
}

void			rotate(t_quaternion	*rot, t_vector3f axis, float angle)
{
	*rot = normalized4(mul4q(new_quaternion4vf(axis, angle), *rot));
}

t_obj			initobj(t_parse *p, int type)
{
	t_obj	obj;

	obj.rot = new_quaternion4f(0, 0, 0, 1);
	rotate(&obj.rot, new_vector3f(1, 0, 0), p->rot_x);
	rotate(&obj.rot, new_vector3f(0, 1, 0), p->rot_y);
	rotate(&obj.rot, new_vector3f(0, 0, 1), p->rot_z);
	obj.pos = new_vector3f(p->pos_x, p->pos_y, p->pos_z);
	obj.color = new_vector3f(p->red, p->green, p->blue);
	obj.diameter = p->diameter;
	obj.intens = p->intens;
	obj.type = type;
	return (obj);
}

t_obj			fill(int fd, int *nb_line, int type)
{
	char	*line;
	int		i;
	t_parse	obj;

	i = 0;
	while (get_next_line(fd, &line) > 0)
	{
		if (ft_strcmp(line, "{") && !i)
			error("error: ", NULL, TRUE, FALSE);
		if (!ft_strcmp(line, "}"))
		{
			free(line);
			break ;
		}
		else if (i)
			fill_obj(&obj, nb_line, line);
		i++;
		free(line);
	}
	*nb_line = *nb_line + 2;
	return (initobj(&obj, type));
}

int				find_obj(t_scene *s, int fd, char *l, int *nl)
{
	if (!ft_strcmp(l, "#camera"))
		s->camera = fill(fd, nl, CAM);
	else if (!ft_strcmp(l, "#proj") && s->elem.nb_proj < MAX_PROJ)
		s->proj[s->elem.nb_proj++] = fill(fd, nl, PROJ);
	else if (!ft_strcmp(l, ".sphere") && s->elem.nb_sphere < MAX_SPHERE)
		s->sphere[s->elem.nb_sphere++] = fill(fd, nl, SPHERE);
	else if (!ft_strcmp(l, ".plan") && s->elem.nb_plan < MAX_PLAN)
		s->plan[s->elem.nb_plan++] = fill(fd, nl, PLAN);
	else if (!ft_strcmp(l, ".cylinder") && s->elem.nb_cylinder < MAX_CYLINDER)
		s->cylinder[s->elem.nb_cylinder++] = fill(fd, nl, CYLINDER);
	else if (!ft_strcmp(l, ".cone") && s->elem.nb_cone < MAX_CONE)
		s->cone[s->elem.nb_cone++] = fill(fd, nl, CONE);
	else if (l[0] != '\0')
		return (error("object error line: ", ft_itoa(*nl), TRUE, FALSE));
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
	scene.elem.count_obj = 0;
	scene.elem.nb_proj = 0;
	scene.elem.nb_sphere = 0;
	scene.elem.nb_plan = 0;
	scene.elem.nb_cylinder = 0;
	scene.elem.nb_cone = 0;
	if (!(fd = open_file(file)))
		return (scene);
	while (get_next_line(fd, &line) > 0)
	{
		scene.elem.count_obj++;
		ft_strtolower(line);
		if (!find_obj(&scene, fd, line, &nb_line))
			scene.elem.count_obj--;
		free(line);
	}
	return (scene);
}
