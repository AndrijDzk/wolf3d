/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/07 10:49:02 by adzikovs          #+#    #+#             */
/*   Updated: 2018/11/24 12:02:48 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <common_typedefs.h>

#include "SDL.h"

#include "libft.h"

#include "t_vec3d_math.h"

#include "common.h"

#include "wolf3d.h"

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
	t_sdl				sdl;
	t_scene				scene;
	t_camera			camera;
	t_xpm_texture		**textures;

	if (argc > 1)
	{
		scene.cont_type = Cont_t_list;
		scene.container.l_surfaces = NULL;
		scene.bsp_tree = NULL;
		if (read_map(argv[1], &scene, &textures))
			return (1);
	}
	else
		return (1);
	if (init(&sdl))
		return (1);
	init_camera(&sdl, &camera);
	render_scene(&sdl, &scene, &camera);
	throw_current_image_on_screen(&sdl);
	main_loop(&sdl, &scene, &camera);
}
