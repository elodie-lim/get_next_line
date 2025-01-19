/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elodlim <elodlim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 20:04:06 by elodlim           #+#    #+#             */
/*   Updated: 2025/01/19 12:01:47 by elodlim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_bzero(void *mem, size_t sz)
{
	while (sz--)
		*(unsigned char *)mem++ = 0;
}

void	*ft_calloc(size_t nmemb, size_t sz)
{
	void	*ptr;
	size_t	msz;

	msz = nmemb * sz;
	if (nmemb == 0 || sz == 0)
	{
		nmemb = 1;
		sz = 1;
	}
	if ((int)nmemb < 0 || (int)sz < 0)
		return (0);
	ptr = malloc(msz);
	if (ptr)
		ft_bzero(ptr, msz);
	return (ptr);
}

ssize_t	ft_index_of(char const *s, char c)
{
	ssize_t	i;

	i = 0;
	while (s[i])
	{
		if (c == s[i])
			return (i);
		i++;
	}
	return (-1);
}

size_t	ft_strlen(char const *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t const	s1sz = ft_strlen(s1);
	size_t const	sz = s1sz + ft_strlen(s2) + 1;
	char			*s;
	size_t			i;

	s = ft_calloc(sz, sizeof(char));
	if (!s)
		return (0);
	i = 0;
	while (i < s1sz)
	{
		s[i] = s1[i];
		i++;
	}
	while (i < sz)
	{
		s[i] = s2[i - s1sz];
		i++;
	}
	return (s);
}
