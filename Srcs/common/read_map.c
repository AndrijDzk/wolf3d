/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 13:26:06 by adzikovs          #+#    #+#             */
/*   Updated: 2018/11/24 10:13:31 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <common_typedefs.h>
#include "bsp.h"

#include "common.h"

static int	read_map_error_exit(int fd,
				t_saved_xpm_texture **saved_txt,
				size_t txt_am,
				t_list **surfaces)
{
	size_t	i;

	if (fd >= 0)
		close(fd);
	if (saved_txt)
	{
		i = 0;
		while (saved_txt[i] && i < txt_am)
		{
			if (saved_txt[i]->texture.colors)
				free(saved_txt[i]->texture.colors);
			if (saved_txt[i]->texture.data)
				free(saved_txt[i]->texture.data);
			i++;
		}
		free(saved_txt);
	}
	t_list_deep_clear(surfaces);
	return (1);
}

static int	replace_scene_data(t_scene *scene, t_list *surfaces)
{
	t_bsp_node				*new_tree;

	if (scene == NULL || surfaces == NULL)
		return (1);
	if ((new_tree = build_bsp_tree_from_t_list(surfaces)) == NULL)
		return (1);
	t_list_deep_clear(&scene->container.l_surfaces);
	scene->container.l_surfaces = surfaces;
	clear_bsp_tree(&scene->bsp_tree);
	scene->bsp_tree = new_tree;
	return (0);
}

static void	unpack_textures(
				t_saved_xpm_texture **saved_txt,
				t_xpm_texture ***textures,
				size_t txt_am)
{
	size_t		i;

	*textures = (t_xpm_texture**)malloc(sizeof(**textures) * (txt_am + 1));
	(*textures)[txt_am] = NULL;
	i = 0;
	while (i < txt_am)
	{
		(*textures)[i] = (t_xpm_texture*)malloc(sizeof(***textures));
		ft_memcpy((*textures)[i], &saved_txt[i]->texture, sizeof(***textures));
		free(saved_txt[i]);
		i++;
	}
	free(saved_txt);
}

int			read_map(char *filename, t_scene *scene, t_xpm_texture ***textures)
{
	int						fd;
	size_t					txt_am;
	t_saved_xpm_texture		**saved_txt;
	t_list					*surfaces;

	if (scene == NULL || textures == NULL || scene->cont_type != Cont_t_list)
		return (1);
	if ((fd = open(filename, O_RDONLY)) < 0)
		return (1);
	if (read(fd, &txt_am, sizeof(txt_am)) != sizeof(txt_am) ||
		txt_am == 0)
		return (read_map_error_exit(fd, NULL, 0, NULL));
	saved_txt = (t_saved_xpm_texture**)malloc(sizeof(*saved_txt) * txt_am);
	ft_bzero(saved_txt, sizeof(*saved_txt) * txt_am);
	if (read_map_textures(fd, saved_txt, txt_am))
		return (read_map_error_exit(fd, saved_txt, txt_am, NULL));
	if ((surfaces = read_map_surfaces(fd, saved_txt)) == NULL)
		return (read_map_error_exit(fd, saved_txt, txt_am, NULL));
	if (replace_scene_data(scene, surfaces))
		return (read_map_error_exit(fd, saved_txt, txt_am, &surfaces));
	unpack_textures(saved_txt, textures, txt_am);
	close(fd);
	return (0);
}
