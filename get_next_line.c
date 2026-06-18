#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>


size_t	ft_strlen(const char *s){
	int i;

	i = 0;
	while(*s){
		s++;
		i++;
	}

	return i;
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


char	*ft_strchr(const char *s, int c){
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

char *get_next_line(int fd){
	char buf[BUFFER_SIZE + 1];
	static char *backup;
	char *line;
	ssize_t n;
	int i;

	while((n = read(fd, buf, BUFFER_SIZE)) > 0){
		buf[n] = '\0';
		if(!backup)
			backup = ft_strdup("");
		backup = ft_strjoin(backup, buf);
		if(ft_strchr(backup, '\n'))
			break;
	}

	return line;
}

int main(){
	int fd = open("example.txt", O_RDONLY);
	if(fd == -1) { perror("open"); return 1;}
	get_next_line(fd);
	close(fd);
	return 0;
}	
