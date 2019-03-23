/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_scene_processor.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 14:18:26 by adzikovs          #+#    #+#             */
/*   Updated: 2018/11/07 14:25:48 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>

#include "common.h"

void		create_slave_params(
				t_renderer_slave_param params[4],
				t_sdl *sdl,
				t_scene *scene,
				t_camera *camera)
{
	int		h_quater;
	int		i;

	h_quater = sdl->window.surface->h / 4;
	i = 0;
	while (i < 4)
	{
		params[i].sdl = sdl;
		params[i].scene = scene;
		params[i].camera = camera;
		params[i].y_start = h_quater * i;
		params[i].y_end = h_quater * (i + 1);
		params[i].x_start = 0;
		params[i].x_end = sdl->window.surface->w;
		i++;
	}
}

int			capture_new_slaves(
				pthread_t slaves[4],
				t_renderer_slave_param params[4])
{
	if (pthread_create(slaves, NULL, raycast_renderer_slave, params))
		return (0);
	if (pthread_create(slaves + 1, NULL, raycast_renderer_slave, params + 1))
		return (1);
	if (pthread_create(slaves + 2, NULL, raycast_renderer_slave, params + 2))
		return (2);
	if (pthread_create(slaves + 3, NULL, raycast_renderer_slave, params + 3))
		return (3);
	return (4);
}

int			render_scene_processor(t_sdl *sdl, t_scene *scene, t_camera *camera)
{
	int						lock;
	int						i;
	t_renderer_slave_param	params[4];
	pthread_t				slaves[4];
	int						ret;

	lock = 0;
	if (SDL_MUSTLOCK(sdl->window.surface))
	{
		if (SDL_LockSurface(sdl->window.surface))
			return (print_sdl_error_and_return("SDL_LockSurface"));
		lock = 1;
	}
	create_slave_params(params, sdl, scene, camera);
	ret = capture_new_slaves(slaves, params);
	i = 0;
	while (i < ret)
	{
		pthread_join(slaves[i], NULL);
		i++;
	}
	draw_crosshair(sdl);
	if (lock)
		SDL_UnlockSurface(sdl->window.surface);
	return (0);
}
