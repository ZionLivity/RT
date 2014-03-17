/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/07 16:53:52 by rbenjami          #+#    #+#             */
/*   Updated: 2014/03/17 18:56:20 by rbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H
# include <lib3d.h>
# include <mlx.h>

# define WIN_H 720
# define WIN_W 1080

# define MAX_PLAN 5
# define MAX_PROJ 5
# define MAX_SPHERE 30
# define MAX_CYLINDER 30
# define MAX_CONE 30

# define TYPE_CAM 0
# define TYPE_PROJ 1
# define TYPE_SPHERE 2
# define TYPE_PLAN 3
# define TYPE_CYLINDER 4
# define TYPE_CONE 5

typedef struct		s_transform
{
	t_vector3f		pos;
	t_quaternion	rot;
	t_vector3f		scale;
}					t_transform;

typedef struct		s_obj
{
	int				type;
	int				red;
	int				green;
	int				blue;
	float			intens;
	float			diameter;
	int				rot_x;
	int				rot_y;
	int				rot_z;
	int				pos_x;
	int				pos_y;
	int				pos_z;
	t_transform		tran;
}					t_obj;

typedef struct		s_line
{
	char			var[50];
	float			value;
}					t_line;

typedef struct		s_color
{
	int				red;
	int				green;
	int				blue;
}					t_color;

typedef struct		s_elem
{
	int				count_obj;
	int				nb_cam;
	int				nb_plan;
	int				nb_proj;
	int				nb_sphere;
	int				nb_cylinder;
	int				nb_cone;
}					t_elem;

typedef struct		s_camera
{
	t_vector3f		pos;
	t_vector3f		forward;
	t_vector3f		up;
	t_vector3f		right;
}					t_camera;

typedef struct		s_scene
{
	int				shadow;
	int				brightness;
	t_elem			elem;
	t_obj			cam;
	t_obj			plan[MAX_PLAN];
	t_obj			proj[MAX_PROJ];
	t_obj			sphere[MAX_SPHERE];
	t_obj			cylinder[MAX_CYLINDER];
	t_obj			cone[MAX_CONE];
}					t_scene;

typedef struct		s_img
{
	void			*img;
	char			*data;
	int				endian;
	int				sizeline;
	int				bpp;
}					t_img;

typedef struct		s_env
{
	t_scene			*scene;
	void			*win;
	void			*mlx;
	t_img			screen;
	t_camera		cam;
}					t_env;

int				error(const char *s1, char *s2, int exit_bool, int details);

/*
**	render.c
*/
int				render(t_env *env, t_scene *scene);
int				fill_img(t_scene *scene, t_img *img, t_camera cam);

/*
**	parse.c
*/
t_scene			parse(char *file);

/*
**	color.c
*/
t_color			rgb(int r, int g, int b);

/*
**	hook.c
*/
int				expose_hook(t_env *e);
int				key_hook(int keycode, t_env *e);

/*
**	camera.c
*/
t_camera		new_camera(t_vector3f pos);
void			move(t_camera *cam, t_vector3f dir, float amt);
void			rotate_x(t_camera *cam, float angle);
void			rotate_y(t_camera *cam, float angle);

/*
**	verify.c
*/
void			check_clean_line(t_line *l, int *nb_line, char *line);

/*
**	utils.c
*/
float			res(float a, float b, float c);

/*
**	inter.c
*/
float			sphere(t_camera cam, t_obj sphere, t_vector3f ray);
float			cylinder(t_camera cam, t_obj cylinder, t_vector3f ray);

#endif /* !RT_H */
