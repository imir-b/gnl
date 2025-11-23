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

char	*ft_add_to_stash(int fd, char *stash, int *end)
{
	char		*buffer;
	char		*readed;
	ssize_t		bytes;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	bytes = read(fd, buffer, BUFFER_SIZE);
	if (bytes == 0)
	{
		*end = 1;
		return (free(buffer), stash);
	}
	if (bytes < 0)
		return (free(buffer), NULL);
	buffer[bytes] = '\0';
	readed = ft_realloc(stash, buffer);
	return (readed);
}

char	*ft_clean_stash(char **stash)
{
	char	*new_stash;
	char	*newline;
	int		i;

	newline = ft_strchr(*stash, '\n');
	newline++;
	new_stash = malloc(ft_strlen(newline) + 1);
	if (!new_stash)
		return (NULL);
	i = 0;
	new_stash[i] = '\0';
	while (newline[i])
	{
		new_stash[i] = newline[i];
		i++;
	}
	new_stash[i] = '\0';
	free (*stash);
	return (new_stash);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;
	char		*newline;
	int			end;

	end = 0;
	if (fd < 0 || fd > 1024 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!stash)
		stash = ft_add_to_stash(fd, stash, &end);
	while (stash && !ft_strchr(stash, '\n') && !end)
		stash = ft_add_to_stash(fd, stash, &end);
	if (!stash)
		return (free(stash), NULL);
	newline = ft_strchr(stash, '\n');
	if (newline)
	{
		line = ft_strndup(stash, newline - stash + 1);
		stash = ft_clean_stash(&stash);
		return (line);
	}
	else
	{
		line = stash;
		stash = NULL;
		return (line);
	}
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
