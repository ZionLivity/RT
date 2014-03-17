/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector2f_pow.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/25 14:55:57 by rbenjami          #+#    #+#             */
/*   Updated: 2014/02/25 14:56:27 by rbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib3d.h"

t_vector2f	pow2f(t_vector2f vec1, float value)
{
	float	x_;
	float	y_;

	x_ = pow(vec1.x, value);
	y_ = pow(vec1.y, value);
	return (new_vector2f(x_, y_));
}
