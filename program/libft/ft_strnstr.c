/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atropnik <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 05:06:46 by atropnik          #+#    #+#             */
/*   Updated: 2019/03/22 23:40:07 by atropnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t len)
{
	size_t		i1;
	size_t		i2;
	size_t		j1;
	size_t		j2;

	if (*s2 == '\0')
		return ((char *)s1);
	i1 = 0;
	j1 = 0;
	while (*(s1 + i1) && i1 < len)
	{
		i2 = i1;
		j2 = j1;
		while (*(s2 + j2) && *(s1 + i2) == *(s2 + j2) && i1 + j2 < len)
		{
			i2++;
			j2++;
		}
		if (*(s2 + j2) == '\0')
			return ((char *)(s1 + i1));
		i1++;
	}
	return (NULL);
}
