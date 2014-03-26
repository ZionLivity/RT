/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/07 16:53:52 by rbenjami          #+#    #+#             */
/*   Updated: 2014/03/26 17:19:04 by rbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H
# include <lib3d.h>
# include <mlx.h>
# include "struct.h"

# define WIN_H 720
# define WIN_W 1080

# define CAM -2
# define PROJ -1

# define AMBIENT 0.25F

# define C 0
# define L 1
# define N 2
# define R 3
# define D 4
# define R2 5

enum		e_obj
{
	SPHERE,
	CYLINDER,
	PLAN,
	CONE
};

/*
**	error.c
*/
int			error(int quit, const char *msg, ...);

/*
**	render.c
*/
int			render(t_env *env, t_scene *scene);
int			fill_img(t_scene *scene, t_img *img, t_camera cam);

/*
**	parse.c
*/
t_scene		parse(char *file);

/*
**	color.c
*/
t_vector3f	rgb(int r, int g, int b);
t_vector3f	rgbv(t_vector3f vec);

/*
**	hook.c
*/
int			expose_hook(t_env *e);
int			key_hook(int keycode, t_env *e);

/*
**	camera.c
*/
t_camera	*new_camera(t_obj *cam);
void		move(t_camera *cam, t_vector3f dir, float amt);
void		rotate_x(t_camera *cam, float angle);
void		rotate_y(t_camera *cam, float angle);
void		rotate_z(t_camera *cam, float angle);

/*
**	verify.c
*/
void		check_clean_line(t_line *l, int *nb_line, char *line);
void		verify_scene(t_scene scene);

/*
**	utils.c
*/
float		res(float a, float b, float c);

/*
**	obj_inter.c
*/
float		sphere(t_vector3f cam, t_obj sphere, t_vector3f ray);
float		cylinder(t_vector3f cam, t_obj cylinder, t_vector3f ray);
float		plan(t_vector3f cam, t_obj plan, t_vector3f ray);
float		cone(t_vector3f pos, t_obj cone, t_vector3f ray);

/*
**	inter.c
*/
t_obj		*inter(t_scene *s, t_vector3f d, t_vector3f o, t_vector3f *i);
t_obj		*inter2(t_scene *scene, t_vector3f ray_d, t_vector3f ray_o);

/*
**	light.c
*/
t_vector3f	diffuse(t_obj p, t_obj o, t_vector3f l, t_vector3f n);
t_vector3f	specular(t_obj p, t_obj o, t_vector3f ray, t_vector3f r);
int			shadows(t_scene *s, t_obj *o, t_vector3f rd, t_vector3f ro);
t_vector3f	reflection(t_scene *s, t_obj *o, t_vector3f pos, t_vector3f ray);

/*
**	obj.c
*/
void		init_type(t_find_type **tab_type);
void		add_obj(t_scene *scene, t_obj *obj);
void		add_proj(t_scene *scene, t_obj *proj);
t_obj		*initobj(t_scene *scene, t_parse *p, int type);
void		init_obj(t_parse *obj);

/*
**	pixel.c
*/
t_vector3f	get_reflected(t_vector3f light_vec, t_vector3f normal);
t_vector3f	get_normal(t_obj obj, t_vector3f inter);
t_vector3f	get_color(t_scene *s, t_obj proj, t_obj *obj, t_vector3f i);

#endif
