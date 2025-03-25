/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eanella <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 21:06:40 by eanella           #+#    #+#             */
/*   Updated: 2025/02/06 21:22:52 by eanella          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*left_c;
	char		*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	left_c = fill_left_c(fd, left_c, buffer);
	free(buffer);
	if (!left_c)
		return (NULL);
	line = set_line(left_c);
	if (!line)
	{
		free(left_c);
		left_c = NULL;
		return (NULL);
	}
	left_c = update_left_c(left_c);
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

/*
#include <fcntl.h>
#include <stdio.h>

int	main(int argc, char **argv)
{
	(void)argc;
    int     fd;
    char    *line;

	fd = open(argv[1], O_RDONLY);
    //fd = 42;
	if (fd == -1)
    {
        perror("Errore nell'apertura del file");
        return (1);
    }
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }
	
	//line = get_next_line(fd);
	//while (line)
	//{
	//	printf("%s", line);
	//	free(line);
	//	line = get_next_line(fd);
	//}
	//printf("%s", line);
    
    close(fd);
    return (0);
}
*/