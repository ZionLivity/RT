/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/24 16:40:11 by rbenjami          #+#    #+#             */
/*   Updated: 2014/03/21 16:13:03 by rbenjami         ###   ########.fr       */
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
	obj->diffuse_cmp = (!ft_strcmp(l.var, "diffuse_cmp")) ? l.value : obj->diffuse_cmp;
	obj->specular_cmp = (!ft_strcmp(l.var, "specular_cmp")) ? l.value : obj->specular_cmp;
	obj->reflection = (!ft_strcmp(l.var, "reflection")) ? l.value : obj->reflection;
	obj->refraction = (!ft_strcmp(l.var, "refraction")) ? l.value : obj->refraction;
}

void			rotate(t_quaternion	*rot, t_vector3f axis, float angle)
{
	*rot = normalized4(mul4q(new_quaternion4vf(axis, angle), *rot));
}

void			add_obj(t_scene *scene, t_obj *obj)
{
	t_objl	*newl;
	t_objl	*tmp;

	if (!(newl = (t_objl *)ft_memalloc(sizeof(t_objl))))
		return ;
	newl->obj = obj;
	newl->next = NULL;
	if (!scene->objl)
		scene->objl = newl;
	else
	{
		tmp = scene->objl;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = newl;
	}
}

void			add_proj(t_scene *scene, t_obj *proj)
{
	t_projl	*newl;
	t_projl	*tmp;

	if (!(newl = (t_projl *)ft_memalloc(sizeof(t_projl))))
		return ;
	newl->proj = proj;
	newl->next = NULL;
	if (!scene->projl)
		scene->projl = newl;
	else
	{
		tmp = scene->projl;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = newl;
	}
}

t_obj			initobj(t_scene *scene, t_parse *p, int type)
{
	t_obj	*obj;

	if (!(obj = (t_obj *)ft_memalloc(sizeof(t_obj))))
		return (*obj);
	obj->rot = new_quaternion4f(0, 0, 0, 1);
	rotate(&obj->rot, new_vector3f(1, 0, 0), p->rot_x);
	rotate(&obj->rot, new_vector3f(0, 1, 0), p->rot_y);
	rotate(&obj->rot, new_vector3f(0, 0, 1), p->rot_z);
	obj->pos = new_vector3f(p->pos_x, p->pos_y, p->pos_z);
	obj->color = new_vector3f(p->red, p->green, p->blue);
	obj->diameter = p->diameter;
	obj->intens = p->intens;
	obj->diffuse_cmp = p->diffuse_cmp;
	obj->specular_cmp = p->specular_cmp;
	obj->type = type;
	obj->refraction = p->refraction;
	obj->reflection = p->reflection;
	if (type >= 0)
		add_obj(scene, obj);
	else if (type == PROJ)
		add_proj(scene, obj);
	return (*obj);
}

t_obj			fill(t_scene *scene, int fd, int *nb_line, int type)
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
		return (error("object error line: ", ft_itoa(*nl), TRUE, FALSE));
	else
		return (0);
	*nl = *nl + 2;
	return (1);
}

void	init_type(find_type **tab_type)
{
	*tab_type = (find_type *)ft_memalloc(sizeof(find_type) * 3);
	(*tab_type)[0] = &sphere;
	(*tab_type)[1] = &cylinder;
	(*tab_type)[2] = &plan;
}

t_scene			parse(char *file)
{
	int		fd;
	char	*line;
	t_scene	scene;
	int		nb_line;

	nb_line = 1;
	scene.objl = NULL;
	init_type(&scene.tab_type);
	scene.count_obj = 0;
	// scene.elem.count_obj = 0;
	// scene.elem.nb_proj = 0;
	// scene.elem.nb_sphere = 0;
	// scene.elem.nb_plan = 0;
	// scene.elem.nb_cylinder = 0;
	// scene.elem.nb_cone = 0;
	if (!(fd = open_file(file)))
		return (scene);
	while (get_next_line(fd, &line) > 0)
	{
		scene.count_obj++;
		ft_strtolower(line);
		if (!find_obj(&scene, fd, line, &nb_line))
			scene.count_obj--;
		free(line);
	}
	return (scene);
}
