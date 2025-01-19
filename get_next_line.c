/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elodlim <elodlim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 20:05:37 by elodlim           #+#    #+#             */
/*   Updated: 2025/01/19 12:13:10 by elodlim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*free_all(char *tmp, char *buffer)
{
	free(tmp);
	free(buffer);
	return (NULL);
}

char	*get_full_line(char *content)
{
	int		i;
	char	*line;

	i = 0;
	while (content[i] && content[i] != '\n')
		i++;
	if (content[i] == '\n')
		i++;
	line = malloc ((i + 1) * sizeof(char));
	if (!line)
		return (NULL);
	ft_strlcpy(line, content, i + 1);
	return (line);
}

char	*update_content(char *content, int line_length)
{
	char	*new_content;
	int		old_length;

	old_length = ft_strlen(content);
	if (line_length < old_length)
		new_content = ft_strdup(content + line_length);
	else
		new_content = ft_strdup("");
	free(content);
	content = new_content;
	return (content);
}

char	*read_file_to_content(char *buffer, int fd)
{
	char	*new_content;
	char	*tmp;
	int		bytes_read;

	tmp = malloc ((BUFFER_SIZE + 1) * sizeof(char));
	if (!tmp)
		return (NULL);
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, tmp, BUFFER_SIZE);
		if (bytes_read < 0 || (bytes_read == 0 && !buffer[0]))
			return (free_all(tmp, buffer));
		tmp[bytes_read] = '\0';
		new_content = ft_strjoin(buffer, tmp);
		free(buffer);
		buffer = new_content;
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	free(tmp);
	return (buffer);
}

char	*get_next_line(int fd)
{
	static char		*buffer;
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!buffer)
		buffer = ft_strdup("");
	if (!buffer)
		return (NULL);
	buffer = read_file_to_content(buffer, fd);
	if (!buffer)
		return (NULL);
	line = get_full_line(buffer);
	if (!line)
	{
		free(buffer);
		buffer = NULL;
		return (NULL);
	}
	buffer = update_content(buffer, ft_strlen(line));
	return (line);
}

// #include <stdio.h>
// #include <fcntl.h>
// int	main(int argc, char const *argv[])
// {
// 	int		fd;
// 	int		lines;
// 	int		start_lines;
// 	char	*s;

// 	if (argc < 2)
// 		fd = 0;
// 	else
// 		fd = open(argv[1], O_RDONLY);
// 	if (argc == 3)
// 		start_lines = atoi(argv[2]);
// 	else
// 		start_lines = 5;
// 	lines = 0;
// 	while (lines < start_lines)
// 	{
// 		s = get_next_line(fd);
// 		printf("%s", s);
// 		free(s);
// 		lines++;
// 	}
// 	return (0);
// }
