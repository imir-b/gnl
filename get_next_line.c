/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbleskin <vbleskin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 02:05:20 by vbleskin          #+#    #+#             */
/*   Updated: 2025/11/19 06:09:09 by vbleskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 10

int	ft_strlen(const char *str)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (*s == (char)c)
		return ((char *)s);
	if (*s == '\0')
		return ((char *)s);
	return (NULL);
}

char	*ft_strndup(const char *s, size_t n)
{
	char	*dest;
	int		i;
	int		len;

	len = 0;
	while (s[len] && len < n)
		len++;
	dest = malloc(len + 1);
	if (!dest)
		return (NULL);
	i = 0;
	while (i <= len)
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_realloc(char *s1, char *s2)
{
	char	*dest;
	int		i;
	int		j;

	dest = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!dest)
		return (NULL);
	i = ((j = 0));
	while (s1[i])
	{
		dest[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		dest[i] = s2[i + j];
		i++;
	}
	dest[i] = '\0';
	free(s1);
	return (dest);
}

char	*get_next_line(int fd)
{
	static char	*stash[1024];
	char		*buffer;
	char		*line;
	ssize_t		bytes;

	if (fd < 0 || fd > 1024 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	while (ft_strchr((const char *)line, '\n') == NULL)
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		line = ft_realloc(line, buffer);
	}
	ft_strndup(line, ft_strchr((const char *)line, '\n'));
	stash[fd];
	free(buffer);
	return (line);
}

int	main(void)
{
	char	*line;

	line = get_next_line(0);
	printf("%s", line);
	line = get_next_line(0);
	printf("%s", line);
	line = get_next_line(0);
	printf("%s", line);
	line = get_next_line(0);
	printf("%s", line);
	line = get_next_line(0);
	printf("%s", line);
	free(line);
	return (0);
}
