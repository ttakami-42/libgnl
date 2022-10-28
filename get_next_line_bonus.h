/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakami <ttakami@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 21:02:57 by ttakami           #+#    #+#             */
/*   Updated: 2022/10/28 22:04:39 by ttakami          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <limits.h>
# include <stdint.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 256
# endif

# ifndef OPEN_MAX
#  include <stdio.h>
#  define OPEN_MAX FOPEN_MAX
# endif

typedef struct s_gnl_asset
{
	char	*buf;
	ssize_t	pre_read_len;
	size_t	total_read_len;
	size_t	allocated_len;
	size_t	delimiter_idx;
}	t_gnl_asset;

size_t	ft_strlen(const char *str);
char	*ft_strcpy(char *dst, const char *src);
char	*get_next_line(int fd);

#endif