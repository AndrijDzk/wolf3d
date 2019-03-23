/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map_surfaces.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 12:58:28 by adzikovs          #+#    #+#             */
/*   Updated: 2018/11/24 10:15:13 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <common_typedefs.h>
#include "common_typedefs.h"

int			check_and_fix_surface_params(t_surface *buff)
{
	if (buff == NULL)
		return (1);
	if ((fabs(buff->plane.norm.y) > DBL_ZERO) ==
		(fabs(buff->plane.norm.x) > DBL_ZERO ||
		fabs(buff->plane.norm.z) > DBL_ZERO))
		return (1);
	if (fabs(buff->plane.norm.y) > DBL_ZERO)
	{
		ft_bzero(&buff->plane.norm, sizeof(buff->plane.norm));
		buff->plane.norm.y = 1;
	}
	else
		buff->plane.norm.y = 0;
	if (buff->length <= 0 || buff->height <= 0)
		return (1);
	return (0);
}

int			check_and_fix_surface_texture(
				t_surface *buff, t_saved_xpm_texture **textures)
{
	size_t	i;

	if (buff == NULL || textures == NULL || buff->visual_type != evtTexture)
		return (1);
	i = 0;
	while (textures[i])
	{
		if (textures[i]->old_data_ptr == buff->visual.texture.data)
		{
			buff->visual.texture.data = textures[i]->texture.data;
			buff->visual.texture.colors = textures[i]->texture.colors;
			return (0);
		}
		i++;
	}
	return (1);
}

int			check_and_fix_surface(
				t_surface *buff, t_saved_xpm_texture **textures)
{
	if (check_and_fix_surface_params(buff))
		return (1);
	if (check_and_fix_surface_texture(buff, textures))
		return (1);
	return (0);
}

t_list		*read_map_surfaces(int fd, t_saved_xpm_texture **textures)
{
	t_list		*res;
	t_surface	buff;
	t_surface	*buff2;
	ssize_t		ret;

	res = NULL;
	while ((ret = read(fd, &buff, sizeof(buff))) == sizeof(buff))
	{
		if (check_and_fix_surface(&buff, textures))
		{
			t_list_deep_clear(&res);
			return (NULL);
		}
		buff2 = (t_surface*)malloc(sizeof(*buff2));
		ft_memcpy(buff2, &buff, sizeof(*buff2));
		t_list_push_back(&res, buff2, sizeof(*buff2));
	}
	return (res);
}
