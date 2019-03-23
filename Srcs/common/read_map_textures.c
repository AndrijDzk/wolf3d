/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map_textures.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 12:42:56 by adzikovs          #+#    #+#             */
/*   Updated: 2018/11/24 12:09:55 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common_typedefs.h"

int		rt_error_exit(t_saved_xpm_texture **res, t_saved_xpm_texture *last,
			t_xpm_color *last_colors, t_saved_xpm_texture *last_data)
{
	size_t	i;

	i = 0;
	while (res[i])
	{
		if (res[i]->texture.data)
			free(res[i]->texture.data);
		if (res[i]->texture.colors)
			free(res[i]->texture.colors);
		free(res[i]);
		res[i] = NULL;
		i++;
	}
	if (last)
		free(last);
	if (last_data)
		free(last_data->texture.data);
	if (last_colors)
		free(last_colors);
	return (1);
}

int		check_texture(t_xpm_texture *txt)
{
	if (txt == NULL)
		return (1);
	if (txt->header.w <= 0 || txt->header.h <= 0 ||
		txt->header.colors == 0 || txt->header.chars_per_pixel != 1)
		return (1);
	if (txt->x[0] != 0 || fabs(txt->x[1] + 1 - txt->header.w) > DBL_ZERO ||
		txt->y[0] != 0 || fabs(txt->y[1] + 1 - txt->header.h) > DBL_ZERO)
		return (1);
	return (0);
}

int		read_map_textures(int fd,
			t_saved_xpm_texture **res, size_t am)
{
	t_saved_xpm_texture	*tmp;
	size_t				size;
	size_t				i;

	i = 0;
	while (i < am)
	{
		tmp = (t_saved_xpm_texture*)malloc(sizeof(*tmp));
		if (read(fd, tmp, sizeof(*tmp)) != sizeof(*tmp))
			return (rt_error_exit(res, tmp, NULL, NULL));
		if (check_texture(&tmp->texture))
			return (rt_error_exit(res, tmp, NULL, NULL));
		size = sizeof(*tmp->texture.colors) * tmp->texture.header.colors;
		tmp->texture.colors = (t_xpm_color*)malloc(size);
		if (read(fd, tmp->texture.colors, size) != (ssize_t)size)
			return (rt_error_exit(res, tmp, tmp->texture.colors, NULL));
		size = (size_t)tmp->texture.header.w * tmp->texture.header.h + 1;
		tmp->texture.data = (char*)malloc(size);
		if (read(fd, tmp->texture.data, size) != (ssize_t)size)
			return (rt_error_exit(res, tmp, tmp->texture.colors, tmp));
		res[i] = tmp;
		i++;
	}
	return (0);
}
