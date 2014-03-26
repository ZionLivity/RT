/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/26 13:56:24 by rbenjami          #+#    #+#             */
/*   Updated: 2014/03/26 15:23:55 by rbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

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
	t_vector3f		f;
	t_vector3f		u;
	t_vector3f		r;
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

typedef float		(*t_find_type)(t_vector3f, t_obj, t_vector3f);

typedef struct		s_scene
{
	int				count_obj;
	t_obj			*camera;
	t_camera		*cam;
	t_projl			*projl;
	t_objl			*objl;
	t_find_type		*tab_type;
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

#endif
