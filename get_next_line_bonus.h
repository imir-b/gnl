/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbleskin <vbleskin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 02:53:56 by vbleskin          #+#    #+#             */
/*   Updated: 2025/12/15 23:32:16 by vbleskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdlib.h>
# include <unistd.h>

int		ft_strlen(const char *str);
char	*ft_strchr(const char *s, int c);
char	*ft_strndup(char *src, size_t n);
char	*ft_realloc(char *s1, char *s2);
char	*ft_add_to_stash(int fd, char *stash, int *end);
char	*ft_clean_stash(char **stash);
char	*get_next_line(int fd);

#endif
