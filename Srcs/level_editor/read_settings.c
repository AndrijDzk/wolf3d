/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_settings.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/17 10:56:30 by adzikovs          #+#    #+#             */
/*   Updated: 2018/11/17 11:03:03 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "level_editor_typedefs.h"

#include "common.h"

#define T_SIZE sizeof(t_xpm_texture)

t_xpm_texture	**read_textures(int fd, enum e_setting *new_setting)
{
	t_list		*tmp;
	char		*line;

	tmp = NULL;
	while (get_next_line(fd, &line) > 0)
	{
		if ((*new_setting = is_setting(line)) != esNot)
		{
			free(line);
			return ((t_xpm_texture**)t_list_to_arr(&tmp));
		}
		else
		{
			t_list_push_back(&tmp, read_xpm_texture(line), T_SIZE);
			free(line);
		}
	}
	free(line);
	return ((t_xpm_texture**)t_list_to_arr(&tmp));
}

int				read_settings(int fd, t_game_data *game_data)
{
	char			*line;
	enum e_setting	setting;

	while (get_next_line(fd, &line) > 0)
	{
		if (is_setting(line) == esTextures)
		{
			if (game_data->textures)
				free_2darr((void**)game_data->textures);
			game_data->textures = read_textures(fd, &setting);
		}
		free(line);
	}
	free(line);
	return (0);
}
