/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hemorais <hemorais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/25 13:44:11 by hemorais          #+#    #+#             */
/*   Updated: 2026/06/25 14:39:33 by hemorais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_strdup(const char *str)
{
	char	*new_str;
	int		i;

	i = 0;
	new_str = malloc(ft_strlen(str) + 1);
	if (!new_str)
		return (NULL);
	while (str[i])
	{
		new_str[i] = str[i];
		i++;
	}
	new_str[i] = '\0';
	return (new_str);
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	int		i;
	int		j;
	char	*str;
	size_t	len;

	len = ft_strlen(s1) + ft_strlen(s2);
	str = malloc(len + 1);
	i = 0;
	j = 0;
	if (!str)
		return (NULL);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		str[i + j] = s2[j];
		j++;
	}
	str[i + j] = '\0';
	return (str);
}

char	*ft_strchr(char *s, int c)
{
	char	*p;

	while (*s)
	{
		if (*s == (unsigned char)c)
		{
			p = s;
			return (p);
		}
		s++;
	}
	if ((unsigned char)c == 0)
	{
		p = s;
	}
	else
	{
		p = NULL;
	}
	return (p);
}

static char	*allocate_size(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	size;

	if (ft_strlen(s) < start)
	{
		substr = malloc(1);
		if (!substr)
			return (NULL);
		*substr = '\0';
		return (substr);
	}
	if (ft_strlen(s) - start > len)
	{
		size = len + 1;
	}
	else
	{
		size = ft_strlen(s) - start + 1;
	}
	substr = malloc(size);
	if (substr == NULL)
		return (NULL);
	return (substr);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	char	*ptr;

	substr = allocate_size(s, start, len);
	if (!substr)
		return (NULL);
	ptr = substr;
	while (start && *s)
	{
		s++;
		start--;
	}
	while (*s && len)
	{
		*ptr = *s;
		ptr++;
		s++;
		len--;
	}
	*ptr = '\0';
	return (substr);
}
