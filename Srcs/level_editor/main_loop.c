/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/12 14:35:27 by adzikovs          #+#    #+#             */
/*   Updated: 2018/11/24 13:20:14 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <common_typedefs.h>
#include "SDL.h"

#include "return_codes.h"

#include "level_editor_defines.h"

#include "level_editor.h"

#include "common.h"

#include "level_editor_typedefs.h"

static void			init_arrays2(SDL_Keycode *key_codes,
						enum e_input_action *action_codes)
{
	action_codes[12] = eiaDecreaseFOV;
	key_codes[12] = SDLK_9;
}

static void			init_arrays(SDL_Keycode *key_codes,
						enum e_input_action *action_codes)
{
	action_codes[0] = eiaRotCameraUp;
	key_codes[0] = SDLK_r;
	action_codes[1] = eiaRotCameraDown;
	key_codes[1] = SDLK_f;
	action_codes[2] = eiaRotCameraLeft;
	key_codes[2] = SDLK_z;
	action_codes[3] = eiaRotCameraRight;
	key_codes[3] = SDLK_x;
	action_codes[4] = eiaMoveCameraForward;
	key_codes[4] = SDLK_w;
	action_codes[5] = eiaMoveCameraBackward;
	key_codes[5] = SDLK_s;
	action_codes[6] = eiaMoveCameraLeft;
	key_codes[6] = SDLK_a;
	action_codes[7] = eiaMoveCameraRight;
	key_codes[7] = SDLK_d;
	action_codes[8] = eiaMoveCameraUp;
	key_codes[8] = SDLK_SPACE;
	action_codes[9] = eiaMoveCameraDown;
	key_codes[9] = SDLK_c;
	action_codes[10] = eiaEscape;
	key_codes[10] = SDLK_ESCAPE;
	action_codes[11] = eiaIncreaseFOV;
	key_codes[11] = SDLK_0;
	init_arrays2(key_codes, action_codes);
}

enum e_input_action	keycode_into_e_input_action(SDL_Keycode key)
{
	size_t						i;
	static char					init = 0;
	static SDL_Keycode			key_codes[LEVEL_EDITOR_BUTTONS_AM];
	static enum e_input_action	action_codes[LEVEL_EDITOR_BUTTONS_AM];

	if (init == 0)
	{
		init_arrays(key_codes, action_codes);
		init = 1;
	}
	i = 0;
	while (i < LEVEL_EDITOR_BUTTONS_AM)
	{
		if (key == key_codes[i])
			return (action_codes[i]);
		i++;
	}
	return (eiaNone);
}

static int			my_exit(t_sdl *sdl)
{
	SDL_DestroyWindow(sdl->window.window);
	SDL_Quit();
	exit(0);
}

int					main_loop(t_sdl *sdl, t_scene *scene,
						t_camera *camera, t_game_data *data)
{
	SDL_Event		event;

	while (1)
	{
		SDL_WaitEvent(&event);
		if (event.type == SDL_KEYDOWN)
		{
			if (camera_movement(sdl, scene, camera,
				keycode_into_e_input_action(event.key.keysym.sym)) == EXIT)
				return (my_exit(sdl));
			else if (process_keydown_le(sdl, data, event))
				return (my_exit(sdl));
		}
		else if (event.type == SDL_MOUSEMOTION)
		{
			if (process_mouse(sdl, scene, camera, &event) == EXIT)
				return (my_exit(sdl));
		}
		else if (event.type == SDL_WINDOWEVENT &&
				event.window.event == SDL_WINDOWEVENT_CLOSE)
			return (my_exit(sdl));
	}
}
