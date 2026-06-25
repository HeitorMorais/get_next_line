#include "get_next_line.h"

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
	return new_str - ft_strlen(str);
}

char *ft_strjoin(const char *s1, const char *s2){
	int	i;
	int	j;
	char	*str;
	size_t len;

	len = ft_strlen(s1) + ft_strlen(s2);
	str = malloc(len + 1);
	i = 0;
	j = 0;
	if(!str)
		return NULL;
	while(s1[i]){
		str[i] = s1[i];
		i++;
	}
	while(s2[j]){
		str[i+j] = s2[j];
		j++;
	}
	str[i+j] = '\0';

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