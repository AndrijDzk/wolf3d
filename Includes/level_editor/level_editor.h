/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   level_editor.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/11 15:03:29 by adzikovs          #+#    #+#             */
/*   Updated: 2018/11/17 14:16:39 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEVEL_EDITOR_H
# define LEVEL_EDITOR_H

# include "level_editor_typedefs.h"

int		init(t_sdl *sdl, t_scene *scene);

int		init_game_data(char *filename, t_game_data *data);

int		main_loop(t_sdl *sdl, t_scene *scene,
			t_camera *camera, t_game_data *data);

int		process_keydown_le(t_sdl *sdl, t_game_data *data, SDL_Event e);

int		select_base_surface(t_sdl *sdl, t_game_data *data, SDL_Event e);

int		create_or_destroy_tmp_surface(t_sdl *sdl, t_game_data *data,
			SDL_Event e);

int		move_tmp_surface(t_sdl *sdl, t_game_data *data, SDL_Event e);

int		rotate_tmp_surface(t_sdl *sdl, t_game_data *data, SDL_Event e);

int		change_tmp_surface(t_sdl *sdl, t_game_data *data, SDL_Event e);

int		read_settings(int fd, t_game_data *game_data);

int		calculate_new_texture_data(
			const t_xpm_texture *old_base,
			const t_xpm_texture *new_base,
			t_xpm_texture *texture_part);

#endif
