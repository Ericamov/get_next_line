/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eanella <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 17:11:13 by eanella           #+#    #+#             */
/*   Updated: 2025/02/20 17:11:13 by eanella          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_next_line(int fd)
{
	static char	*left_c[FD_LIMIT];
	char		*buffer;
	char		*line;

	if (fd < 0 || fd >= FD_LIMIT || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	left_c[fd] = fill_left_c(fd, left_c[fd], buffer);
	free(buffer);
	if (!left_c[fd])
		return (NULL);
	line = set_line(left_c[fd]);
	if (!line)
	{
		free(left_c[fd]);
		left_c[fd] = NULL;
		return (NULL);
	}
	left_c[fd] = update_left_c(left_c[fd]);
	return (line);
}

char	*fill_left_c(int fd, char *left_c, char *buffer)
{
	ssize_t	bytes_read;
	char	*temp;
	char	*newline_pos;

	if (!left_c)
		left_c = ft_strdup("");
	if (!left_c)
		return (NULL);
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	while (bytes_read > 0)
	{
		buffer[bytes_read] = 0;
		temp = ft_strjoin(left_c, buffer);
		if (!temp)
			return (free(left_c), NULL);
		free(left_c);
		left_c = temp;
		newline_pos = ft_strchr(left_c, '\n');
		if (newline_pos)
			break ;
		bytes_read = read(fd, buffer, BUFFER_SIZE);
	}
	if (bytes_read == -1)
		return (free(left_c), NULL);
	return (left_c);
}

char	*set_line(char *left_c)
{
	char	*newline_pos;
	char	*line;
	size_t	len;

	if (!left_c || *left_c == '\0')
		return (NULL);
	newline_pos = ft_strchr(left_c, '\n');
	if (newline_pos)
		len = (newline_pos - left_c) + 1;
	else
		len = ft_strlen(left_c);
	line = (char *)malloc(sizeof(char) * (len + 1));
	if (!line)
		return (NULL);
	ft_strlcpy(line, left_c, len + 1);
	return (line);
}

char	*update_left_c(char *left_c)
{
	char	*newline_pos;
	char	*new_left_c;

	if (!left_c)
		return (NULL);
	newline_pos = ft_strchr(left_c, '\n');
	if (!newline_pos)
	{
		free(left_c);
		return (NULL);
	}
	new_left_c = ft_strdup(newline_pos + 1);
	free(left_c);
	if (!new_left_c || *new_left_c == '\0')
	{
		free(new_left_c);
		return (NULL);
	}
	return (new_left_c);
}
