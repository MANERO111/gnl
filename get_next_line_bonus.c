/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakioud <aakioud@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/13 17:01:05 by aakioud           #+#    #+#             */
/*   Updated: 2026/11/13 17:02:43 by aakioud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*bfree(char *s1, char *s2)
{
	free(s1);
	free(s2);
	return (NULL);
}

static char	*update_str(char *str)
{
	char	*new_str;
	int		i;
	int		j;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (!str[i])
	{
		free(str);
		return (NULL);
	}
	new_str = malloc(sizeof(char) * (ft_strlen(str) - i));
	if (!new_str)
	{
		free(str);
		return (NULL);
	}
	i++;
	j = 0;
	while (str[i])
		new_str[j++] = str[i++];
	new_str[j] = '\0';
	free(str);
	return (new_str);
}

static char	*gettline(char *str)
{
	char	*line ;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!str || !str[0])
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	line = malloc(sizeof(char) * (i + 1));
	if (!line)
		return (NULL);
	while (j < i)
	{
		line[j] = str[j];
		j++;
	}
	line[j] = '\0';
	return (line);
}

static char	*read_and_fill(int fd, char *str)
{
	char	*buffer;
	char	*new;
	ssize_t	byte_reads;

	buffer = malloc(sizeof(char) * (((size_t)BUFFER_SIZE) + 1 ));
	if (!buffer)
	{
		free(str);
		return (NULL);
	}
	byte_reads = 1;
	while (!ft_strchr(str, '\n') && byte_reads > 0)
	{
		byte_reads = read(fd, buffer, BUFFER_SIZE);
		if (byte_reads == -1)
			return (bfree(str, buffer));
		buffer[byte_reads] = '\0';
		new = ft_strjoin(str, buffer);
		if (!new)
			return (bfree(str, buffer));
		str = new;
	}
	free(buffer);
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*str[OPEN_MAX];
	char		*line;

	if (fd < 0 || fd >= OPEN_MAX || BUFFER_SIZE <= 0)
		return (NULL);
	str[fd] = read_and_fill(fd, str[fd]);
	if (!str[fd])
		return (NULL);
	line = gettline(str[fd]);
	str[fd] = update_str(str[fd]);
	return (line);
}
