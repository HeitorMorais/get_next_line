#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

#define BUFFER_SIZE 2048

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
	//backup = ft_substr();
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
