/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbleskin <vbleskin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 02:05:20 by vbleskin          #+#    #+#             */
/*   Updated: 2025/11/23 18:53:36 by vbleskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>
// #define BUFFER_SIZE 10
#include "get_next_line.h"

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
	{
		if (stash)
			free(stash);
		*end = 1;
		return (free(buffer), NULL);
	}
	buffer[bytes] = '\0';
	readed = ft_realloc(stash, buffer);
	return (readed);
}

char	*ft_clean_stash(char **stash)
{
	char	*new_stash;
	char	*nl;
	int		i;

	nl = ft_strchr(*stash, '\n');
	nl++;
	new_stash = malloc(ft_strlen(nl) + 1);
	if (!new_stash)
		return (NULL);
	i = 0;
	new_stash[i] = '\0';
	while (nl[i])
	{
		new_stash[i] = nl[i];
		i++;
	}
	new_stash[i] = '\0';
	free (*stash);
	return (new_stash);
}

char	*get_next_line(int fd)
{
	static char	*stash[1024];
	char		*line;
	char		*nl;
	int			end;

	end = 0;
	if (fd < 0 || fd >= 1024 || BUFFER_SIZE <= 0)
		return (NULL);
	while (!end && (!stash[fd] || !ft_strchr(stash[fd], '\n')))
		stash[fd] = ft_add_to_stash(fd, stash[fd], &end);
	if (!stash[fd])
		return (free(stash[fd]), NULL);
	nl = ft_strchr(stash[fd], '\n');
	if (nl)
	{
		line = ft_strndup(stash[fd], nl - stash[fd] + 1);
		stash[fd] = ft_clean_stash(&stash[fd]);
		return (line);
	}
	line = stash[fd];
	stash[fd] = NULL;
	return (line);
}

// int	main(void)
// {
// 	char	*line;

// 	while ((line = get_next_line(0)) != NULL)
// 	{
// 		printf("%s", line);
// 		free(line);
// 	}
// 	return (0);
// }
