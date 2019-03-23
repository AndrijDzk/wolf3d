/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/07 10:49:02 by adzikovs          #+#    #+#             */
/*   Updated: 2018/11/24 10:50:53 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "common.h"

#include "level_editor.h"

static void		init_camera(t_sdl *sdl, t_camera *camera)
{
	camera->focal_length = -200;
	camera->x_scale = 2;
	camera->y_scale = 2;
	ft_bzero(camera->m, sizeof(**camera->m) * 16);
	camera->m[0][0] = 1;
	camera->m[1][1] = 1;
	camera->m[2][2] = 1;
	camera->m[2][3] = 200;
	camera->m[3][3] = 1;
	camera->w = sdl->window.surface->w;
	camera->h = sdl->window.surface->h;
}

int				main(int argc, char **argv)
{
	t_sdl		sdl;
	t_scene		scene;
	t_camera	camera;
	t_game_data	data;

	if (init(&sdl, &scene))
		return (1);
	init_camera(&sdl, &camera);
	data.scene = &scene;
	data.camera = &camera;
	if (argc < 2 || init_game_data(argv[1], &data))
		return (1);
	render_scene(&sdl, &scene, &camera);
	throw_current_image_on_screen(&sdl);
	main_loop(&sdl, &scene, &camera, &data);
}
