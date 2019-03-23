/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_camera.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/14 12:43:22 by adzikovs          #+#    #+#             */
/*   Updated: 2018/10/15 11:28:02 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "return_codes.h"

#include "matrix_math.h"

#include "common.h"

#define ROTATE_SPEED 0.1

int		rotate_camera_around_x(t_sdl *sdl, t_scene *scene, t_camera *camera,
			enum e_input_action action)
{
	if (action == eiaRotCameraUp)
		rotate_crd_system_around_x(camera->m, ROTATE_SPEED);
	else if (action == eiaRotCameraDown)
		rotate_crd_system_around_x(camera->m, -ROTATE_SPEED);
	render_scene(sdl, scene, camera);
	throw_current_image_on_screen(sdl);
	return (OK);
}

int		rotate_camera_around_y(t_sdl *sdl, t_scene *scene, t_camera *camera,
			enum e_input_action action)
{
	if (action == eiaRotCameraLeft)
		rotate_crd_system_around_world_y(camera->m, ROTATE_SPEED);
	else if (action == eiaRotCameraRight)
		rotate_crd_system_around_world_y(camera->m, -ROTATE_SPEED);
	render_scene(sdl, scene, camera);
	throw_current_image_on_screen(sdl);
	return (OK);
}
