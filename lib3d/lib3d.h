/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/25 11:28:51 by rbenjami          #+#    #+#             */
/*   Updated: 2014/03/24 11:11:22 by rbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIB3D_H
# define LIB3D_H
# include <math.h>

typedef struct			s_vector2f
{
	float				x;
	float				y;
}						t_vector2f;

typedef struct			s_vector3f
{
	float				x;
	float				y;
	float				z;
}						t_vector3f;

typedef struct			s_quaternion
{
	float				x;
	float				y;
	float				z;
	float				w;
}						t_quaternion;

typedef struct			s_matrix4f
{
	float				m[4][4];
}						t_matrix4f;

/*
**	vector2f
*/
t_vector2f		new_vector2f(float x, float y);
float			length2(t_vector2f vec);
float			dot2(t_vector2f vec1, t_vector2f vec2);
float			cross2(t_vector2f vec1, t_vector2f vec2);
t_vector2f		normalized2(t_vector2f vec);
t_vector2f		inv2(t_vector2f vec);
t_vector2f		add2v(t_vector2f vec1, t_vector2f vec2);
t_vector2f		sub2v(t_vector2f vec1, t_vector2f vec2);
t_vector2f		mul2v(t_vector2f vec1, t_vector2f vec2);
t_vector2f		div2v(t_vector2f vec1, t_vector2f vec2);
t_vector2f		add2f(t_vector2f vec1, float value);
t_vector2f		sub2f(t_vector2f vec1, float value);
t_vector2f		mul2f(t_vector2f vec1, float value);
t_vector2f		div2f(t_vector2f vec1, float value);
t_vector2f		pow2f(t_vector2f vec1, float value);
t_vector2f		rt2(t_vector2f vec1);
t_vector2f		rotate2(t_vector2f vec, float angle);
float			get_value2(t_vector2f vec);

/*
**	vector3f
*/
t_vector3f		new_vector3f(float x, float y, float z);
float			length3(t_vector3f vec);
float			dot3(t_vector3f vec1, t_vector3f vec2);
t_vector3f		cross3(t_vector3f vec1, t_vector3f vec2);
t_vector3f		normalized3(t_vector3f vec);
t_vector3f		inv3(t_vector3f vec);
t_vector3f		add3v(t_vector3f vec1, t_vector3f vec2);
t_vector3f		sub3v(t_vector3f vec1, t_vector3f vec2);
t_vector3f		mul3v(t_vector3f vec1, t_vector3f vec2);
t_vector3f		div3v(t_vector3f vec1, t_vector3f vec2);
t_vector3f		add3f(t_vector3f vec1, float value);
t_vector3f		sub3f(t_vector3f vec1, float value);
t_vector3f		mul3f(t_vector3f vec1, float value);
t_vector3f		div3f(t_vector3f vec1, float value);
t_vector3f		pow3f(t_vector3f vec1, float value);
t_vector3f		rt3(t_vector3f vec1);
t_vector3f		rotate3(t_vector3f vec, t_vector3f axis, float angle);
t_vector3f		rotate3q(t_vector3f vec, t_quaternion rotation);
float			get_value3(t_vector3f vec);

/*
**	matrix4f
*/
t_matrix4f		new_matrix4();
t_matrix4f		mul4m(t_matrix4f m, t_matrix4f r);
t_matrix4f		init_rotation3f(float x, float y, float z);
t_matrix4f		init_translation(t_vector3f vec);
t_matrix4f		init_rotation3v(t_vector3f f, t_vector3f u, t_vector3f r);
t_matrix4f		init_scale(float x, float y, float z);

/*
**	quaternion
*/
t_quaternion	new_quaternion4f(float x, float y, float z, float w);
t_quaternion	new_quaternion4vf(t_vector3f axis, float angle);
float			length4(t_quaternion q);
t_quaternion	normalized4(t_quaternion q);
t_quaternion	conjugate4(t_quaternion q);
t_matrix4f		to_rotation_matrix(t_quaternion q);
t_quaternion	mul4q(t_quaternion q, t_quaternion r);
t_quaternion	mul4v(t_quaternion q, t_vector3f r);

/*
**	transforms
*/
t_vector3f		transform(t_vector3f v, t_matrix4f m);
t_vector3f		get_transforms(t_vector3f v, t_vector3f t, t_quaternion r);

/*
**	utils
*/
float			to_radians(float angle);
float			rt(float val);

#endif /* !LIB3D_H */
