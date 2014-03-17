/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector2f_mul.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/25 11:54:07 by rbenjami          #+#    #+#             */
/*   Updated: 2014/02/25 14:11:11 by rbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib3d.h"

t_vector2f	mul2f(t_vector2f vec1, float value)
{
	return (new_vector2f(vec1.x * value, vec1.y * value));
}

t_vector2f	mul2v(t_vector2f vec1, t_vector2f vec2)
{
	return (new_vector2f(vec1.x * vec2.x, vec1.y * vec2.y));
}
