/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 12:28:01 by adzikovs          #+#    #+#             */
/*   Updated: 2018/11/24 13:30:08 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <common_typedefs.h>
#include "common_typedefs.h"

int		save_texture(int fd, t_xpm_texture *texture)
{
	t_saved_xpm_texture		buff;
	size_t					s;

	if (fd < 0 || texture == NULL)
		return (1);
	ft_memcpy(&buff.texture, texture, sizeof(buff.texture));
	buff.old_data_ptr = texture->data;
	write(fd, &buff, sizeof(buff));
	s = sizeof(*texture->colors) * texture->header.colors;
	write(fd, texture->colors, s);
	write(fd, texture->data, ft_strlen(texture->data) + 1);
	return (0);
}

int		save_textures(int fd, t_xpm_texture **textures)
{
	size_t					i;

	if (fd < 0 || textures == NULL || *textures == NULL)
		return (1);
	i = 0;
	while (textures[i])
		i++;
	write(fd, &i, sizeof(i));
	i = 0;
	while (textures[i])
	{
		if (save_texture(fd, textures[i]))
			return (1);
		i++;
	}
	return (0);
}

int		save_surfaces(int fd, t_list *surfaces)
{
	if (fd < 0)
		return (1);
	while (surfaces)
	{
		write(fd, surfaces->data, surfaces->size);
		surfaces = surfaces->next;
	}
	return (0);
}

int		save_map(t_xpm_texture **textures, t_scene *scene)
{
	int	fd;

	if (textures == NULL || *textures == NULL ||
		scene->cont_type != Cont_t_list)
		return (1);
	if ((fd = open("out.map", O_WRONLY | O_CREAT | O_TRUNC,
		S_IWUSR | S_IRUSR)) < 0)
		return (1);
	if (save_textures(fd, textures))
		return (1);
	if (save_surfaces(fd, scene->container.l_surfaces))
		return (1);
	close(fd);
	return (0);
}
