/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_xpm_texture.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 12:52:59 by adzikovs          #+#    #+#             */
/*   Updated: 2018/11/19 13:51:00 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

static void			*read_xpm_texture_error_exit(int fd, t_xpm_texture *res)
{
	close(fd);
	if (res)
	{
		if (res->colors)
			free(res->colors);
		free(res->data);
		free(res);
	}
	return (NULL);
}

static void			init_res(t_xpm_texture **res)
{
	*res = (t_xpm_texture*)malloc(sizeof(**res));
	(*res)->x[0] = 0;
	(*res)->y[0] = 0;
	(*res)->colors = NULL;
	(*res)->data = (char*)malloc(1);
	(*res)->data[0] = 0;
}

static void			init_res2(t_xpm_texture *res)
{
	res->x[1] = res->header.w - 1;
	res->y[1] = res->header.h - 1;
}

static void			join(t_xpm_texture *res, char *line)
{
	char			*tmp;

	tmp = res->data;
	res->data = ft_strjoin(res->data, line);
	free(tmp);
	free(line);
}

t_xpm_texture		*read_xpm_texture(char *filename)
{
	int				fd;
	char			*line;
	t_xpm_texture	*res;

	if (filename == NULL)
		return (NULL);
	if ((fd = open(filename, O_RDONLY)) < 0)
		return (NULL);
	init_res(&res);
	if (read_xpm_header(fd, &res->header))
		return (read_xpm_texture_error_exit(fd, res));
	init_res2(res);
	if ((res->colors = read_xpm_colors(fd, res->header.colors)) == NULL)
		return (read_xpm_texture_error_exit(fd, res));
	while (get_next_line(fd, &line) > 0)
		join(res, line);
	free(line);
	if (ft_strlen(res->data) != (size_t)(res->header.w * res->header.h))
		return (read_xpm_texture_error_exit(fd, res));
	close(fd);
	return (res);
}
