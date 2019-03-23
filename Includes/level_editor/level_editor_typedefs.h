/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   level_editor_typedefs.h                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/22 14:23:40 by adzikovs          #+#    #+#             */
/*   Updated: 2018/11/17 11:03:03 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEVEL_EDITOR_TYPEDEFS_H
# define LEVEL_EDITOR_TYPEDEFS_H

# include "common_typedefs.h"

enum				e_setting {esNot, esTextures};

enum e_setting		is_setting(char *line);

typedef struct		s_game_data
{
	t_scene			*scene;
	t_camera		*camera;
	t_surface		*new_surface;
	char			exists;
	t_surface		*base_surface;
	t_xpm_texture	**textures;
}					t_game_data;

typedef int			(*t_le_keydown_handler)(t_sdl *, t_game_data *, SDL_Event);

#endif
