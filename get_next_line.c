#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

#define BUFFER_SIZE 2048

size_t	ft_strlen(const char *s){
	int i;

	i = 0;
	while(*s){
		s++;
		i++;
	}

	return i;
}

char	*ft_strdup(const char *str){
	char	*new_str;

	new_str = malloc(ft_strlen(str) + 1);
	if(!new_str)
		return NULL;
	while(*str){
		*new_str = *str;
		new_str++;
		str++;
	}
	*new_str = '\0';
	return new_str;
}

char *ft_strjoin(const char *s1, const char *s2){
	char	*str;
	size_t len;

	len = ft_strlen(s1) + ft_strlen(s2);
	str = malloc(len + 1);
	if(!str)
		return NULL;
	while(*s1){
		*str = *s1;
		s1++;
		str++;
	}
	while(*s2){
		*str = *s2;
		s2++;
		str++;
	}
	*str = '\0';
	str -= len;

	return str;
}


char	*ft_strchr(char *s, int c){
	char *p;

	while(*s)
	{
		if(*s == (unsigned char) c)
		{
			p = s;
			return (p);
		}
		s++;
	}
	if((unsigned char)c == 0)
	{
 		p = s;
	}
	else 
	{
		p = NULL;
	}
	return (p);
}

char	*allocate_line(char *backup){
	char *line;
	size_t len;
	int	i;

	i = 0;
	len = 0;
	while(backup[i] != '\0' && backup[i] != '\n')
	{
		i++;
	}
	if(backup[i] == '\n')
		i++;
	len = i;
	line = malloc(len + 1);
	if(!line)
		return NULL;
	line[i] = '\0';
	while(i-- >= 0)
	{
		line[i] = backup[i];
	}
	return line;
}

char *get_next_line(int fd){
	char buf[BUFFER_SIZE + 1];
	static char *backup;
	char *line;
	ssize_t n;
	while((n = read(fd, buf, BUFFER_SIZE)) > 0){
		buf[n] = '\0';
		if(!backup)
			backup = ft_strdup("");
		backup = ft_strjoin(backup, buf);
		if(ft_strchr(backup, '\n'))
			break;
	}
	line = allocate_line(backup - n);
	while(*backup != '\0' && *backup != '\n')
		backup++;
	backup++;
	return line;
}

int main(){
	int fd = open("example.txt", O_RDONLY);
	if(fd == -1) { perror("open"); return 1;}
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	close(fd);
	return 0;
}	
