/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elodlim <elodlim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 13:35:03 by elodlim           #+#    #+#             */
/*   Updated: 2025/01/19 13:35:03 by elodlim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_bzero(void *mem, size_t n)
{
	while (n--)
		*(unsigned char *)mem++ = 0;
}

void	*ft_calloc(size_t element_count, size_t element_size)
{
	void	*ptr;
	size_t	total_size;

	total_size = element_count * element_size;
	if (element_count == 0 || element_size == 0)
	{
		element_count = 1;
		element_size = 1;
	}
	if ((int)element_count < 0 || (int)element_size < 0)
		return (0);
	ptr = malloc(total_size);
	if (ptr)
		ft_bzero(ptr, total_size);
	return (ptr);
}

ssize_t	strchr_index(char const *s, char c)
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
