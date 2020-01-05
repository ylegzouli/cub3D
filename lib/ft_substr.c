/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylegzoul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 11:00:48 by ylegzoul          #+#    #+#             */
/*   Updated: 2019/11/07 12:12:43 by ylegzoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_subnull(void)
{
	char *s;

	s = malloc(1);
	s[0] = 0;
	return (s);
}

char		*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*s2;
	size_t			j;

	j = 0;
	s2 = 0;
	if (len == 0 || s == 0)
		return (ft_subnull());
	while (s[j] && j < start)
		j++;
	if (j != start)
		return (ft_subnull());
	j = 0;
	while (s[start + j] && j < len)
		j++;
	if (!(s2 = malloc(j + 1)))
		return (0);
	j = 0;
	while (s[start + j] && j < len)
	{
		s2[j] = s[j + start];
		j++;
	}
	s2[j] = 0;
	return (s2);
}
