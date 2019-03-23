/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/13 17:42:12 by adzikovs          #+#    #+#             */
/*   Updated: 2018/10/15 10:42:55 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "return_codes.h"

#include "libft.h"

#include "matrix_math.h"

#include "common.h"

#define ROTATE_SPEED -0.003

int		process_mouse(t_sdl *sdl, t_scene *scene, t_camera *camera,
			SDL_Event *event)
{
	int		x;
	int		y;

	if (event->type == SDL_MOUSEMOTION)
	{
		x = event->motion.xrel;
		y = event->motion.yrel;
		if (x)
			rotate_crd_system_around_world_y(camera->m, x * ROTATE_SPEED);
		if (y)
			rotate_crd_system_around_x(camera->m, y * ROTATE_SPEED);
		render_scene(sdl, scene, camera);
		throw_current_image_on_screen(sdl);
		return (OK);
	}
	return (OK);
}
