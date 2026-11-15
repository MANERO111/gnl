/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakioud <aakioud@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/13 17:01:17 by aakioud           #+#    #+#             */
/*   Updated: 2026/11/15 14:46:42 by aakioud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
	char	*line;
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

	buffer = malloc(sizeof(char) * (((size_t)BUFFER_SIZE) + 1));
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
	static char	*str;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	str = read_and_fill(fd, str);
	if (!str)
		return (NULL);
	line = gettline(str);
	str = update_str(str);
	return (line);
}
