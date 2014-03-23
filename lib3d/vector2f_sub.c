/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector2f_sub.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/25 11:53:30 by rbenjami          #+#    #+#             */
/*   Updated: 2014/03/23 17:21:08 by rbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib3d.h"

t_vector2f	sub2f(t_vector2f vec1, float value)
{
	return (new_vector2f(vec1.x - value, vec1.y - value));
}

t_vector2f	sub2v(t_vector2f vec1, t_vector2f vec2)
{
	return (new_vector2f(vec1.x - vec2.x, vec1.y - vec2.y));
}

t_vector2f	inv2(t_vector2f vec)
{
	return (new_vector2f(-vec.x, -vec.y));
}
