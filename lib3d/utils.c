/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/25 12:01:51 by rbenjami          #+#    #+#             */
/*   Updated: 2014/03/24 18:17:18 by rbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib3d.h"

float		to_radians(float angle)
{
	return (angle * M_PI / 180);
}

float		rt(float val)
{
	return (val * val);
}
