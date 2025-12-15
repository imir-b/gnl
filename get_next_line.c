/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlad <vlad@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 02:05:20 by vbleskin          #+#    #+#             */
/*   Updated: 2025/12/15 06:35:38 by vlad             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include "get_next_line.h"

char	*ft_add_to_stash(int fd, char *stash, int *end)
{
	char		*buffer;
	char		*readed;
	ssize_t		bytes;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
	{
		if (stash)
			free(stash);
		return (*end = -1, NULL);
	}
	bytes = read(fd, buffer, BUFFER_SIZE);
	if (bytes == 0)
		return (*end = 1, free(buffer), stash);
	if (bytes < 0)
	{
		if (stash)
			free(stash);
		return (*end = -1, free(buffer), NULL);
	}
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
		return (NULL);
	if (!stash[fd])
		return (NULL);
	nl = ft_strchr(stash[fd], '\n');
	if (nl)
	{
		line = ft_strndup(stash[fd], nl - stash[fd] + 1);
		stash[fd] = ft_clean_stash(&stash[fd]);
		if (!line)
			free(stash[fd]);
		return (line);
	}
	line = stash[fd];
	stash[fd] = NULL;
	return (line);
}

// int	main(void)
// {
// 	int		fd;
// 	char	*line;
// 	int		i;

// 	i = 1;
// 	fd = open("multiple_nl.txt", O_RDONLY);
// 	if (fd == -1)
// 	{
// 		perror("Erreur ouverture");
// 		return (1);
// 	}
// 	printf("--- Début du test avec BUFFER_SIZE = %d ---\n", BUFFER_SIZE);
// 	while ((line = get_next_line(fd)) != NULL)
// 	{
// 		printf("Ligne %d : |%s| (len: %d)\n", i, line, ft_strlen(line));
// 		free(line);
// 		i++;
// 	}
// 	printf("--- Fin de lecture ---\n");
// 	close(fd);
// 	return (0);
// }
