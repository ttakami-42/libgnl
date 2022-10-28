/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakami <ttakami@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 14:23:28 by ttakami           #+#    #+#             */
/*   Updated: 2022/10/28 22:03:40 by ttakami          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static	char	*ft_strndup(const char *src, size_t len);
static	char	*gnl_join(char *save, t_gnl_asset *gnl);
static	char	*gnl_read(int fd, char *save, t_gnl_asset *gnl);
static	char	*gnl_split(char *save, char **line, t_gnl_asset gnl);

char	*get_next_line(int fd)
{
	static char	*save;
	char		*line;
	t_gnl_asset	gnl;

	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE > SIZE_MAX)
		return (NULL);
	gnl.allocated_len = (size_t)BUFFER_SIZE + 1;
	gnl.pre_read_len = 1;
	gnl.total_read_len = 0;
	gnl.delimiter_idx = 0;
	gnl.buf = (char *)malloc(gnl.allocated_len * sizeof(char));
	if (!gnl.buf)
	{
		free(save);
		save = NULL;
		return (NULL);
	}
	save = gnl_read(fd, save, &gnl);
	if (!save)
		return (NULL);
	line = NULL;
	save = gnl_split(save, &line, gnl);
	return (line);
}

static	char	*ft_strndup(const char *src, size_t len)
{
	char	*result;
	size_t	i;

	result = (char *)malloc((len) * sizeof(char));
	if (!result)
		return (NULL);
	i = 0;
	while (i < len - 1 && src[i] != '\0')
	{
		result[i] = src[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}

static	char	*gnl_join(char *save, t_gnl_asset *gnl)
{
	char	*result;
	size_t	save_size;

	save_size = gnl->total_read_len;
	gnl->total_read_len += (size_t)gnl->pre_read_len;
	if (!save)
		return (ft_strndup(gnl->buf, gnl->allocated_len));
	if (gnl->total_read_len >= gnl->allocated_len)
	{
		while (gnl->total_read_len >= gnl->allocated_len)
			gnl->allocated_len = (gnl->allocated_len * 2) - 1;
		result = ft_strndup(save, gnl->allocated_len);
		if (!result)
		{
			free(save);
			return (NULL);
		}
		free(save);
		ft_strcpy(result + save_size, gnl->buf);
		return (result);
	}
	ft_strcpy(save + save_size, gnl->buf);
	return (save);
}

static	char	*gnl_read(int fd, char *save, t_gnl_asset *gnl)
{
	if (save != NULL)
		gnl->total_read_len += ft_strlen(save);
	while (gnl->pre_read_len && (!save || save[gnl->delimiter_idx] != '\n'))
	{
		gnl->pre_read_len = read(fd, gnl->buf, BUFFER_SIZE);
		if (gnl->pre_read_len == -1)
		{
			free(save);
			free(gnl->buf);
			return (NULL);
		}
		gnl->buf[gnl->pre_read_len] = '\0';
		save = gnl_join(save, gnl);
		if (!save)
			break ;
		while (save[gnl->delimiter_idx] != '\0' \
				&& save[gnl->delimiter_idx] != '\n')
			gnl->delimiter_idx++;
	}
	free(gnl->buf);
	return (save);
}

static	char	*gnl_split(char *save, char **line, t_gnl_asset gnl)
{
	char	*result;
	size_t	new_save_len;

	if (save[gnl.delimiter_idx] == '\n')
		gnl.delimiter_idx++;
	if (*save)
		*line = ft_strndup(save, gnl.delimiter_idx + 1);
	if (!*line || !save[gnl.delimiter_idx])
	{
		free(save);
		return (NULL);
	}
	new_save_len = gnl.allocated_len - gnl.delimiter_idx + 1;
	result = ft_strndup(save + gnl.delimiter_idx, new_save_len);
	if (!result)
	{
		free(*line);
		*line = NULL;
	}
	free(save);
	return (result);
}
