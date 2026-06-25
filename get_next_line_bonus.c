/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hemorais <hemorais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/25 13:44:14 by hemorais          #+#    #+#             */
/*   Updated: 2026/06/25 14:40:56 by hemorais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (*s)
	{
		s++;
		i++;
	}
	return (i);
}

static char	*allocate_line(char *backup)
{
	char	*line;
	size_t	len;
	int		i;

	i = 0;
	len = 0;
	while (backup[i] != '\0' && backup[i] != '\n')
	{
		i++;
	}
	if (backup[i] == '\n')
		i++;
	len = i;
	line = malloc(len + 1);
	if (!line)
		return (NULL);
	line[i] = '\0';
	i--;
	while (i >= 0)
	{
		line[i] = backup[i];
		i--;
	}
	return (line);
}

static char	*reallocate_backup(char *backup[4096], int fd)
{
	char	*temp;
	char	*line;

	if (!backup[fd] || *backup[fd] == '\0')
	{
		free(backup[fd]);
		backup[fd] = NULL;
		return (NULL);
	}
	line = allocate_line(backup[fd]);
	if (!line)
		return (NULL);
	temp = backup[fd];
	backup[fd] = ft_substr(temp, ft_strlen(line), ft_strlen(temp)
			- ft_strlen(line));
	free(temp);
	return (line);
}

char	*get_next_line(int fd)
{
	char		*buf;
	static char	*backup[4096];
	char		*temp;
	ssize_t		n;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buf = malloc(BUFFER_SIZE + 1);
	n = read(fd, buf, BUFFER_SIZE);
	while (n > 0)
	{
		buf[n] = '\0';
		if (!backup[fd])
			backup[fd] = ft_strdup("");
		temp = backup[fd];
		backup[fd] = ft_strjoin(temp, buf);
		free(temp);
		if (ft_strchr(backup[fd], '\n'))
			break ;
		n = read(fd, buf, BUFFER_SIZE);
	}
	free(buf);
	return (reallocate_backup(backup, fd));
}
