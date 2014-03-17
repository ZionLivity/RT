/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/20 11:50:44 by rbenjami          #+#    #+#             */
/*   Updated: 2014/03/11 12:35:27 by rbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char		*ft_strtrim(char const *s)
{
	int		len;

	if (!s)
		return (NULL);
	while (*s && ft_isspace(*s))
		s++;
	len = ft_strlen(s) - 1;
	while (len > 0 && s[len] && ft_isspace(s[len]))
		len--;
	return (ft_strsub(s, 0, len + 1));
}
