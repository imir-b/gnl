/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbleskin <vbleskin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 02:05:20 by vbleskin          #+#    #+#             */
/*   Updated: 2025/11/21 13:51:38 by vbleskin         ###   ########.fr       */
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

char	*ft_strndup(char *src, size_t n)
{
	char	*dest;
	size_t	i;
	size_t	len;

	len = 0;
	while (src[len] && len < n)
		len++;
	dest = malloc(len + 1);
	if (!dest)
		return (NULL);
	i = 0;
	dest[i] = 0;
	while (i < len)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strdup(char *src)
{
	char	*dest;
	int		i;

	dest = malloc(ft_strlen(src) + 1);
	if (!dest)
		return (NULL);
	i = 0;
	dest[i] = '\0';
	while (dest[i])
	{
		dest[i] = src[i];
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

	if (!s1)
		return (free(s1), s2);
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
		dest[i + j] = s2[j];
		j++;
	}
	dest[i + j] = '\0';
	return (free(s1), free(s2), dest);
}

char	*ft_read_line(int fd, int buf_size)
{
	char		*buffer;
	char		*readed;
	ssize_t		bytes;

	readed = malloc(1);
	if (!readed)
		return (NULL);
	readed[0] = '\0';
	while (ft_strchr(readed, '\n') == NULL || readed[0] == '\0')
	{
		buffer = malloc(sizeof(char) * (buf_size + 1));
		if (!buffer)
			return (free(readed), NULL);
		bytes = read(fd, buffer, buf_size);
		if (bytes < 0)
			return (free(buffer), free(readed), NULL);
		if (bytes == 0)
		{
			free (buffer);
			break ;
		}
		buffer[bytes] = '\0';
		readed = ft_realloc(readed, buffer);
	}
	return (readed);
}

char	*get_next_line(int fd)
{
	char		*readed;
	static char	*stash[1024];
	char		*line;
	char		*newline;

	if (fd < 0 || fd > 1024 || BUFFER_SIZE <= 0)
		return (NULL);
	readed = malloc(1);
	if (!readed)
		return (NULL);
	readed[0] = '\0';
	if (stash[fd])
	{
		readed = ft_realloc(readed, ft_strdup(stash[fd]));
		free(stash[fd]);
		stash[fd] = NULL;
	}
	if (!ft_strchr(readed, '\n'))
		readed = ft_realloc(readed, ft_read_line(fd, BUFFER_SIZE));
	if (readed[0] == '\0')
		return (free(readed), NULL);
	newline = ft_strchr(readed, '\n');
	if (newline)
	{
		line = ft_strndup(readed, newline - readed + 1);
		stash[fd] = ft_strdup(newline + 1);
	}
	else
		line = ft_strdup(readed);
	return (free(readed), line);
}

int	main(void)
{
	char	*line;

	while ((line = get_next_line(0)) != NULL)
	{
		printf("%s", line);
		free(line);
	}
	return (0);
}
