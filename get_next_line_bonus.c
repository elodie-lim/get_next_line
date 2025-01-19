/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elodlim <elodlim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 13:34:09 by elodlim           #+#    #+#             */
/*   Updated: 2025/01/19 13:34:09 by elodlim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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

char	*trim_buffer(char *content, int line_length)
{
	char	*updated_buffer;
	int		old_length;

	old_length = ft_strlen(content);
	if (line_length < old_length)
		updated_buffer = ft_strdup(content + line_length);
	else
		updated_buffer = ft_strdup("");
	free(content);
	content = updated_buffer;
	return (content);
}

char	*read_into_buffer(char *buffer, int fd)
{
	char	*updated_buffer;
	char	*tmp;
	int		bytes_read;

	tmp = malloc ((BUFFER_SIZE + 1) * sizeof(char));
	if (!tmp)
		return (NULL);
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, tmp, BUFFER_SIZE);
		if (bytes_read < 0 || (bytes_read <= 0 && !buffer[0]))
			return (free_all(tmp, buffer));
		tmp[bytes_read] = '\0';
		updated_buffer = ft_strjoin(buffer, tmp);
		free(buffer);
		buffer = updated_buffer;
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	free(tmp);
	return (buffer);
}

char	*get_next_line(int fd)
{
	static char		*buffer[NB_FILES];
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!buffer[fd])
		buffer[fd] = ft_strdup("");
	if (!buffer[fd])
		return (NULL);
	buffer[fd] = read_into_buffer(buffer[fd], fd);
	if (!buffer[fd])
		return (NULL);
	line = get_full_line(buffer[fd]);
	if (!line)
	{
		free(buffer[fd]);
		buffer[fd] = NULL;
		return (NULL);
	}
	buffer[fd] = trim_buffer(buffer[fd], ft_strlen(line));
	return (line);
}
