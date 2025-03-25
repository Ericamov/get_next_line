/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eanella <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 21:12:33 by eanella           #+#    #+#             */
/*   Updated: 2025/02/06 21:12:33 by eanella          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		i++;
	}
	return (i);
}

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	src_len;

	src_len = ft_strlen(src);
	i = 0;
	if (size == 0)
	{
		return (src_len);
	}
	while (src[i] != '\0' && i < size - 1)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (src_len);
}

char	*ft_strdup(const char *s)
{
	size_t	i;
	char	*dup;

	i = 0;
	dup = malloc(ft_strlen(s) + 1);
	if (!dup)
	{
		return (NULL);
	}
	while (s[i] != '\0')
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	size;
	size_t	s1_len;

	if (!s1 || !s2)
	{
		return (NULL);
	}
	s1_len = ft_strlen(s1);
	size = s1_len + ft_strlen(s2) + 1;
	str = (char *)malloc(size);
	if (!str)
	{
		return (NULL);
	}
	ft_strlcpy(str, s1, size);
	ft_strlcpy(str + s1_len, s2, size - s1_len);
	return (str);
}

char	*ft_strchr(const char *s, int c)
{
	size_t	i;
	char	letter;

	i = 0;
	letter = (char)c;
	while (s[i])
	{
		if (s[i] == letter)
		{
			return ((char *)&s[i]);
		}
		i++;
	}
	if (letter == '\0')
	{
		return ((char *)&s[i]);
	}
	return (NULL);
}
