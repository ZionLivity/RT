/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector3f_mul.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/25 11:30:34 by rbenjami          #+#    #+#             */
/*   Updated: 2014/03/02 20:07:05 by rbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib3d.h"

t_vector3f	mul3f(t_vector3f vec1, float value)
{
	return (new_vector3f(vec1.x * value, vec1.y * value, vec1.z * value));
}

t_vector3f	mul3v(t_vector3f vec1, t_vector3f vec2)
{
	return (new_vector3f(vec1.x * vec2.x, vec1.y * vec2.y, vec1.z * vec2.z));
}
