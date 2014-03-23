/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/07 16:53:52 by rbenjami          #+#    #+#             */
/*   Updated: 2014/03/23 19:50:11 by rbenjami         ###   ########.fr       */
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

# define CAM -2
# define PROJ -1

#define COLOR 0
#define NORMAL 1
#define LIGHT_VEC 2
#define REFLECTED 3

enum		e_obj
{
	SPHERE,
	CYLINDER,
	PLAN,
	CONE
};

# define AMBIENT 0.25F

typedef struct		s_transform
{
	t_vector3f		pos;
	t_quaternion	rot;
	t_vector3f		scale;
}					t_transform;

typedef struct		s_parse
{
	int				type;
	int				red;
	int				green;
	int				blue;
	float			intens;
	float			diameter;
	int				refrac;
	int				reflec;
	int				rot_x;
	int				rot_y;
	int				rot_z;
	int				pos_x;
	int				pos_y;
	int				pos_z;
	int				diffuse;
	int				specular;
}					t_parse;

typedef struct		s_camera
{
	t_vector3f		pos;
	t_vector3f		ray;
	t_vector3f		forward;
	t_vector3f		up;
	t_vector3f		right;
}					t_camera;

typedef struct		s_obj
{
	int				type;
	int				diffuse;
	int				specular;
	int				refrac;
	int				reflec;
	float			diameter;
	float			intens;
	t_vector3f		color;
	t_vector3f		pos;
	t_quaternion	rot;
	t_vector3f		scale;
	t_camera		*cam;
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

typedef struct		s_objl
{
	t_obj			*obj;
	struct s_objl	*next;
}					t_objl;

typedef struct		s_projl
{
	t_obj			*proj;
	struct s_projl	*next;
}					t_projl;

typedef	float	(*find_type)(t_vector3f, t_obj, t_vector3f);

typedef struct		s_scene
{
	int				count_obj;
	t_obj			camera;
	t_camera		cam;
	t_projl			*projl;
	t_objl			*objl;
	find_type		*tab_type;
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
t_color			rgbv(t_vector3f vec);

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
void			rotate_z(t_camera *cam, float angle);

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
float			sphere(t_vector3f cam, t_obj sphere, t_vector3f ray);
float			cylinder(t_vector3f cam, t_obj cylinder, t_vector3f ray);
float			plan(t_vector3f cam, t_obj plan, t_vector3f ray);

/*
**	light.c
*/
t_vector3f	diffuse(t_obj proj, t_obj obj, t_vector3f light_vec, t_vector3f normal);
t_vector3f	specular(t_obj proj, t_obj obj, t_vector3f ray, t_vector3f reflected);
int			shadows(t_scene *scene, t_obj *obj, t_vector3f ray_d, t_vector3f ray_o);

#endif /* !RT_H */
