/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_scene.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/11 17:36:08 by adzikovs          #+#    #+#             */
/*   Updated: 2018/11/07 14:24:11 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "SDL.h"

#include "libft.h"

#include "t_vec3d_math.h"
#include "matrix_math.h"
#include "common.h"

#include "rasterization.h"

void		draw_crosshair(t_sdl *sdl)
{
	int				i;
	int				j;
	SDL_Color		color;

	color.r = 255;
	color.g = 255;
	color.b = 255;
	color.a = 255;
	j = sdl->window.surface->w / 2;
	i = 0;
	while (i < sdl->window.surface->h)
	{
		draw_point(sdl, &color, j, i);
		i++;
	}
	j = sdl->window.surface->h / 2;
	i = 0;
	while (i < sdl->window.surface->w)
	{
		draw_point(sdl, &color, i, j);
		i++;
	}
}

int			render_scene(t_sdl *sdl, t_scene *scene, t_camera *camera)
{
	size_t	i;

	i = 0;
	while (i < MAX_WINDOW_HEIGHT)
	{
		t_list_deep_clear(sdl->window.screen_data + i);
		i++;
	}
	renderer_scene_rasterization(sdl, scene, camera);
	return (0);
}
