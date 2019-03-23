/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_camera.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/12 15:49:01 by adzikovs          #+#    #+#             */
/*   Updated: 2018/10/27 15:53:02 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "return_codes.h"

#include "t_vec3d_math.h"

#include "common.h"

#define MOVE_SPEED 30

void	move_camera(t_camera *camera, t_vec3d const *dir, double speed)
{
	t_vec3d		dir_tmp;
	t_vec3d		pos;

	pos.x = camera->m[0][3];
	pos.y = camera->m[1][3];
	pos.z = camera->m[2][3];
	dir_tmp = t_vec3d_scal_mult(dir, speed);
	pos = t_vec3d_add(&pos, &dir_tmp);
	camera->m[0][3] = pos.x;
	camera->m[1][3] = pos.y;
	camera->m[2][3] = pos.z;
}

int		move_camera_along_x(t_sdl *sdl, t_scene *scene, t_camera *camera,
			enum e_input_action action)
{
	t_vec3d		dir;

	dir.x = camera->m[0][0];
	dir.y = camera->m[1][0];
	dir.z = camera->m[2][0];
	if (action == eiaMoveCameraLeft)
		move_camera(camera, &dir, -MOVE_SPEED);
	else if (action == eiaMoveCameraRight)
		move_camera(camera, &dir, MOVE_SPEED);
	render_scene(sdl, scene, camera);
	throw_current_image_on_screen(sdl);
	return (OK);
}

int		move_camera_along_y(t_sdl *sdl, t_scene *scene, t_camera *camera,
			enum e_input_action action)
{
	t_vec3d		dir;

	dir.x = camera->m[0][1];
	dir.y = camera->m[1][1];
	dir.z = camera->m[2][1];
	if (action == eiaMoveCameraUp)
		move_camera(camera, &dir, MOVE_SPEED);
	else if (action == eiaMoveCameraDown)
		move_camera(camera, &dir, -MOVE_SPEED);
	render_scene(sdl, scene, camera);
	throw_current_image_on_screen(sdl);
	return (OK);
}

int		move_camera_along_z(t_sdl *sdl, t_scene *scene, t_camera *camera,
			enum e_input_action action)
{
	t_vec3d		dir;

	dir.x = camera->m[0][2];
	dir.y = camera->m[1][2];
	dir.z = camera->m[2][2];
	if (action == eiaMoveCameraForward)
		move_camera(camera, &dir, -MOVE_SPEED);
	else if (action == eiaMoveCameraBackward)
		move_camera(camera, &dir, MOVE_SPEED);
	render_scene(sdl, scene, camera);
	throw_current_image_on_screen(sdl);
	return (OK);
}
