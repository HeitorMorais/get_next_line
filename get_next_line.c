#include "get_next_line.h"

#define BUFFER_SIZE 2048

char	*get_next_line(int fd)
{
	char buf[BUFFER_SIZE + 1];
	static char *backup[4096];
	char *temp;
	char *line;
	ssize_t n;
	while ((n = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[n] = '\0';
		if (!backup[fd])
			backup[fd] = ft_strdup("");
		temp = backup[fd];
		backup[fd] = ft_strjoin(temp, buf);
		free(temp);
		if (ft_strchr(backup[fd], '\n'))
			break ;
	}
	line = allocate_line(backup[fd]);
	temp = backup[fd];
	backup[fd] = ft_substr(temp, ft_strlen(line), ft_strlen(temp)
			- ft_strlen(line));
	free(temp);
	return (line);
}