/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elodlim <elodlim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 20:05:37 by elodlim           #+#    #+#             */
/*   Updated: 2025/01/21 00:15:29 by elodlim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*join_and_free(char *dest, char *src)
{
	char	*new_str;

	if (!dest)
		return (NULL);
	new_str = ft_strjoin(dest, src);
	free(dest);
	return (new_str);
}

char	*remove_extracted_line(char *buffer)
{
	int		i;
	int		j;
	char	*line;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
	{
		free(buffer);
		return (NULL);
	}
	line = ft_calloc((ft_strlen(buffer) - i + 1), sizeof(char));
	if (!line)
		return (NULL);
	i++;
	j = 0;
	while (buffer[i])
		line[j++] = buffer[i++];
	free(buffer);
	return (line);
}

char	*extract_line(char *buffer)
{
	char	*line;
	int		i;

	i = 0;
	if (!buffer[i])
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	line = ft_calloc(i + 1 + (buffer[i] == '\n'), sizeof(char));
	if (!line)
		return (0);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] == '\n')
		line[i] = '\n';
	return (line);
}

char	*read_to_buffer(int fd, char *existing_content)
{
	char	*buffer;
	int		bytes_read;

	if (!existing_content)
		existing_content = ft_calloc(1, 1);
	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buffer)
		return (NULL);
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		existing_content = join_and_free(existing_content, buffer);
		if (strchr_index(buffer, '\n') >= 0)
			break ;
	}
	free(buffer);
	return (existing_content);
}

char	*get_next_line(int fd)
{
	static char	*buffer = 0;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		free(buffer);
		buffer = 0;
		return (NULL);
	}
	buffer = read_to_buffer(fd, buffer);
	if (!buffer)
		return (NULL);
	line = extract_line(buffer);
	buffer = remove_extracted_line(buffer);
	return (line);
}

// #include <stdio.h>
// #include <fcntl.h>
// int	main(int argc, char const *argv[])
// {
// 	int		fd;
// 	int		lines_read;
// 	int		nb_lines_to_read;
// 	char	*s;

// 	if (argc < 2)
// 		fd = 0;
// 	else
// 		fd = open(argv[1], O_RDONLY);
// 	if (argc == 3)
// 		nb_lines_to_read = atoi(argv[2]);
// 	else
// 		nb_lines_to_read = 5;
// 	lines_read = 0;
// 	while (lines_read < nb_lines_to_read)
// 	{
// 		s = get_next_line(fd);
// 		printf("%s", s);
// 		free(s);
// 		lines_read++;
// 	}
// 	return (0);
// }
