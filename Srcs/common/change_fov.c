/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_fov.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/24 11:27:45 by adzikovs          #+#    #+#             */
/*   Updated: 2018/11/24 11:31:32 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

#define FOV_SPEED 10

int		change_fov(t_sdl *sdl, t_scene *scene, t_camera *camera,
			enum e_input_action action)
{
	if (sdl == NULL || scene == NULL || camera == NULL)
		return (1);
	if (action == eiaIncreaseFOV)
	{
		if (camera->focal_length < -FOV_SPEED)
			camera->focal_length += FOV_SPEED;
	}
	else if (action == eiaDecreaseFOV)
		camera->focal_length -= FOV_SPEED;
	render_scene(sdl, scene, camera);
	throw_current_image_on_screen(sdl);
	return (0);
}
