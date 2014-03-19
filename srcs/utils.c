/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/25 14:49:31 by rbenjami          #+#    #+#             */
/*   Updated: 2014/03/19 11:11:15 by rbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

float		res(float a, float b, float c)
{
	float	det;
	float	t;
	float	t2;

	det = rt(b) - 4 * a * c;
	t = -1;
	if (det >= 0)
	{
		t = (-b + (float)sqrt(det)) / (a + a);
		if ((t2 = (-b - (float)sqrt(det)) / (a + a)) < t)
			t = t2;
	}
	return (t);
}
