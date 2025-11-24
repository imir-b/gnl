/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbleskin <vbleskin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 02:05:20 by vbleskin          #+#    #+#             */
/*   Updated: 2025/11/24 14:15:07 by vbleskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#define BUFFER_SIZE 10
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
	if (*nl == '\0')
		return (free (*stash), NULL);
	new_stash = malloc(ft_strlen(nl) + 1);
	if (!new_stash)
		return (free(*stash), NULL);
	i = 0;
	new_stash[i] = '\0';
	while (nl[i])
	{
		new_stash[i] = nl[i];
		i++;
	}
	new_stash[i] = '\0';
	return (free (*stash), new_stash);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;
	char		*nl;
	int			end;

	end = 0;
	if (fd < 0 || fd >= 1024 || BUFFER_SIZE <= 0)
		return (NULL);
	while (!end && (!stash || !ft_strchr(stash, '\n')))
		stash = ft_add_to_stash(fd, stash, &end);
	if (!stash)
		return (free(stash), NULL);
	nl = ft_strchr(stash, '\n');
	if (nl)
	{
		line = ft_strndup(stash, nl - stash + 1);
		stash = ft_clean_stash(&stash);
		return (line);
	}
	line = stash;
	stash = NULL;
	return (line);
}

// int    main(int ac, char *av[])
// {
//     int        fd;
//     char    *line;

//     fd = open(av[1], O_RDONLY);
//     (void) ac;
//     line = get_next_line(fd);
//     while (line) {
//         printf("%s", line);
//         free(line);
//         line = get_next_line(fd);
//     }
//     free(line);
// 	close(fd);
//     return (0);
// }

int	main(void)
{
	char *line;
	line = get_next_line(0);
	printf("-%s\n", line);
	free(line);
	line = get_next_line(0);
	printf("-%s\n", line);
	free(line);
	line = get_next_line(0);
	printf("-%s\n", line);
	free(line);
}