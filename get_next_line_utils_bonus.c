/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlad <vlad@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 02:53:54 by vbleskin          #+#    #+#             */
/*   Updated: 2025/12/16 12:13:51 by vlad             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	ft_gnl_strlen(const char *str)
{
	int	len;

	if (!str)
		return (0);
	len = 0;
	while (str[len])
		len++;
	return (len);
}

char	*ft_gnl_strchr(const char *s, int c)
{
	if (!s)
		return (NULL);
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

char	*ft_gnl_strndup(char *src, size_t n)
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
		return (ft_gnl_strndup(s2, ft_gnl_strlen(s2)));
	dest = malloc(ft_gnl_strlen(s1) + ft_gnl_strlen(s2) + 1);
	if (!dest)
		return (free (s1), NULL);
	i = 0;
	while (s1[i])
	{
		dest[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		dest[i + j] = s2[j];
		j++;
	}
	dest[i + j] = '\0';
	return (free(s1), dest);
}
