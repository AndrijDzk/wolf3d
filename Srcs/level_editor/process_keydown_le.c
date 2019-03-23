/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_keydown_le.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/22 14:27:24 by adzikovs          #+#    #+#             */
/*   Updated: 2018/11/24 12:45:17 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "return_codes.h"

#include "level_editor_defines.h"

#include "level_editor.h"

#include "common.h"

static int		save_map_dec(t_sdl *sdl, t_game_data *data, SDL_Event e)
{
	if (e.key.keysym.sym != SDLK_F5 || sdl == NULL || data == NULL)
		return (1);
	if (save_map(data->textures, data->scene))
	{
		ft_printf("Save error!\n");
		return (1);
	}
	else
	{
		ft_printf("Map saved!\n");
		return (0);
	}
}

static void		init_arrays2(SDL_Keycode *codes, t_le_keydown_handler *handlers)
{
	codes[11] = SDLK_KP_1;
	handlers[11] = &change_tmp_surface;
	codes[12] = SDLK_KP_2;
	handlers[12] = &change_tmp_surface;
	codes[13] = SDLK_KP_4;
	handlers[13] = &change_tmp_surface;
	codes[14] = SDLK_KP_5;
	handlers[14] = &change_tmp_surface;
	codes[15] = SDLK_KP_7;
	handlers[15] = &change_tmp_surface;
	codes[16] = SDLK_KP_8;
	handlers[16] = &change_tmp_surface;
	codes[17] = SDLK_v;
	handlers[17] = &change_tmp_surface;
	codes[18] = SDLK_b;
	handlers[18] = &change_tmp_surface;
	codes[19] = SDLK_n;
	handlers[19] = &change_tmp_surface;
	codes[20] = SDLK_m;
	handlers[20] = &change_tmp_surface;
	codes[21] = SDLK_F5;
	handlers[21] = &save_map_dec;
}

static void		init_arrays(SDL_Keycode *codes, t_le_keydown_handler *handlers)
{
	codes[0] = SDLK_RETURN;
	handlers[0] = &create_or_destroy_tmp_surface;
	codes[1] = SDLK_BACKSPACE;
	handlers[1] = &create_or_destroy_tmp_surface;
	codes[2] = SDLK_l;
	handlers[2] = &move_tmp_surface;
	codes[3] = SDLK_j;
	handlers[3] = &move_tmp_surface;
	codes[4] = SDLK_i;
	handlers[4] = &move_tmp_surface;
	codes[5] = SDLK_k;
	handlers[5] = &move_tmp_surface;
	codes[6] = SDLK_y;
	handlers[6] = &move_tmp_surface;
	codes[7] = SDLK_h;
	handlers[7] = &move_tmp_surface;
	codes[8] = SDLK_u;
	handlers[8] = &rotate_tmp_surface;
	codes[9] = SDLK_o;
	handlers[9] = &rotate_tmp_surface;
	codes[10] = SDLK_p;
	handlers[10] = &rotate_tmp_surface;
	init_arrays2(codes, handlers);
}

int				process_keydown_le(t_sdl *sdl, t_game_data *data, SDL_Event e)
{
	static char						flag = 1;
	static SDL_Keycode				codes[LEVEL_EDITOR_EDIT_BUTTONS_AM];
	static t_le_keydown_handler		handlers[LEVEL_EDITOR_EDIT_BUTTONS_AM];
	size_t							i;

	if (flag)
		init_arrays(codes, handlers);
	i = 0;
	while (i < LEVEL_EDITOR_EDIT_BUTTONS_AM)
	{
		if (e.key.keysym.sym == codes[i])
			return ((*(handlers[i]))(sdl, data, e));
		i++;
	}
	return (0);
}
