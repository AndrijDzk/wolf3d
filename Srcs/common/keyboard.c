/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/12 14:39:29 by adzikovs          #+#    #+#             */
/*   Updated: 2018/10/15 12:59:02 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "return_codes.h"

#include "common_defines.h"

#include "common.h"

static void	init_arrays(enum e_input_action *codes, t_keydown_handler *handlers)
{
	codes[0] = eiaRotCameraUp;
	handlers[0] = &rotate_camera_around_x;
	codes[1] = eiaRotCameraDown;
	handlers[1] = &rotate_camera_around_x;
	codes[2] = eiaRotCameraLeft;
	handlers[2] = &rotate_camera_around_y;
	codes[3] = eiaRotCameraRight;
	handlers[3] = &rotate_camera_around_y;
	codes[4] = eiaMoveCameraForward;
	handlers[4] = &move_camera_along_z;
	codes[5] = eiaMoveCameraBackward;
	handlers[5] = &move_camera_along_z;
	codes[6] = eiaMoveCameraLeft;
	handlers[6] = &move_camera_along_x;
	codes[7] = eiaMoveCameraRight;
	handlers[7] = &move_camera_along_x;
	codes[8] = eiaMoveCameraUp;
	handlers[8] = &move_camera_along_y;
	codes[9] = eiaMoveCameraDown;
	handlers[9] = &move_camera_along_y;
	codes[10] = eiaIncreaseFOV;
	handlers[10] = &change_fov;
	codes[11] = eiaDecreaseFOV;
	handlers[11] = &change_fov;
}

int			camera_movement(t_sdl *sdl, t_scene *scene, t_camera *camera,
				enum e_input_action action)
{
	size_t						i;
	static enum e_input_action	codes[COMMON_BUTTONS_AM];
	static t_keydown_handler	handlers[COMMON_BUTTONS_AM];
	static int					init = 0;

	if (init == 0)
	{
		init_arrays(codes, handlers);
		init = 1;
	}
	if (action == eiaEscape)
		return (EXIT);
	i = 0;
	while (i < COMMON_BUTTONS_AM)
	{
		if (action == codes[i])
			return ((*handlers[i])(sdl, scene, camera, action));
		i++;
	}
	return (OK);
}
