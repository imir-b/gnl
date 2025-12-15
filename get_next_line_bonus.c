/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbleskin <vbleskin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 02:53:59 by vbleskin          #+#    #+#             */
/*   Updated: 2025/12/15 03:10:10 by vbleskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_add_to_stash(int fd, char *stash, int *end)
{
	char		*buffer;
	char		*readed;
	ssize_t		bytes;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (*end = -1, NULL);
	bytes = read(fd, buffer, BUFFER_SIZE);
	if (bytes == 0)
		return (*end = 1, free(buffer), stash);
	if (bytes < 0)
		return (*end = -1, free(buffer), NULL);
	buffer[bytes] = '\0';
	readed = ft_realloc(stash, buffer);
	free(buffer);
	if (!readed)
		return (*end = -1, NULL);
	if (bytes < BUFFER_SIZE)
		return (*end = 1, readed);
	return (readed);
}

char	*ft_clean_stash(char **stash)
{
	char	*new_stash;
	char	*nl;
	int		i;

	nl = ft_strchr(*stash, '\n');
	nl++;
	if (*nl == '\0')
		return (free(*stash), NULL);
	new_stash = malloc(ft_strlen(nl) + 1);
	if (!new_stash)
		return (free (*stash), NULL);
	i = 0;
	new_stash[i] = '\0';
	while (nl[i])
	{
		new_stash[i] = nl[i];
		i++;
	}
	new_stash[i] = '\0';
	return (free(*stash), new_stash);
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
	if (end == -1)
		return (free(stash[fd]), NULL);
	if (!stash[fd])
		return (NULL);
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
