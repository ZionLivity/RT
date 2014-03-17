/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector2f_div.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/25 11:55:04 by rbenjami          #+#    #+#             */
/*   Updated: 2014/02/25 14:10:45 by rbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib3d.h"

t_vector2f	div2f(t_vector2f vec1, float value)
{
	return (new_vector2f(vec1.x / value, vec1.y / value));
}

t_vector2f	div2v(t_vector2f vec1, t_vector2f vec2)
{
	return (new_vector2f(vec1.x / vec2.x, vec1.y / vec2.y));
}
