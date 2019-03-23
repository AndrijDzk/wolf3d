/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/11 16:23:41 by adzikovs          #+#    #+#             */
/*   Updated: 2018/10/14 15:56:25 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common_defines.h"

#include "common.h"

#include "level_editor.h"

static int		create_window(t_sdl *sdl)
{
	size_t		i;

	sdl->window.window = SDL_CreateWindow("SDL_RenderClear",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		1024, 768,
		0);
	if (sdl->window.window == NULL)
	{
		SDL_Quit();
		return (print_sdl_error_and_return("SDL_CreateWindow Error"));
	}
	i = 0;
	while (i < MAX_WINDOW_HEIGHT)
	{
		sdl->window.screen_data[i] = NULL;
		i++;
	}
	return (0);
}

static int		get_window_surface(t_sdl *sdl)
{
	sdl->window.surface = SDL_GetWindowSurface(sdl->window.window);
	if (sdl->window.surface == NULL)
		return (print_sdl_error_and_return("SDL_GetWindowSurface Error"));
	if (sdl->window.surface->format == NULL ||
		sdl->window.surface->w <= 0 ||
		sdl->window.surface->h <= 0 ||
		sdl->window.surface->h > MAX_WINDOW_HEIGHT)
	{
		ft_printf("Wrong window surface!\n");
		return (1);
	}
	return (0);
}

static int		init_scene(t_scene *scene)
{
	if (scene == NULL)
		return (1);
	scene->cont_type = Cont_t_list;
	scene->container.l_surfaces = NULL;
	scene->surfaces_am = 0;
	scene->bsp_tree = NULL;
	return (0);
}

int				init_game_data(char *filename, t_game_data *data)
{
	int			fd;

	if ((fd = open(filename, O_RDONLY)) < 0)
		return (1);
	data->new_surface = NULL;
	data->exists = 0;
	data->base_surface = NULL;
	data->textures = NULL;
	if (read_settings(fd, data))
	{
		close(fd);
		return (1);
	}
	close(fd);
	if (data->textures == NULL || data->textures[0] == NULL)
		return (1);
	return (0);
}

int				init(t_sdl *sdl, t_scene *scene)
{
	if (SDL_Init(SDL_INIT_VIDEO))
		return (print_sdl_error_and_return("SDL_Init Error"));
	if (SDL_GetDesktopDisplayMode(0, &(sdl->display_mode)))
	{
		SDL_Quit();
		return (1);
	}
	if (create_window(sdl))
		return (1);
	SDL_RaiseWindow(sdl->window.window);
	if (get_window_surface(sdl))
		return (1);
	SDL_SetRelativeMouseMode(SDL_TRUE);
	if (init_scene(scene))
		return (1);
	return (0);
}
