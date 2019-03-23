/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/11 16:23:41 by adzikovs          #+#    #+#             */
/*   Updated: 2018/11/24 13:55:43 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

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

/*
** static int		create_renderer(t_sdl *sdl)
** {
** 	sdl->window.renderer = SDL_CreateRenderer(sdl->window.window, -1, 0);
** 	if (sdl->window.renderer == NULL)
** 	{
** 		SDL_DestroyWindow(sdl->window.window);
** 		SDL_Quit();
** 		return (print_error_and_return("SDL_CreateRenderer Error"));
** 	}
** 	if (SDL_GetRendererOutputSize(sdl->window.renderer,
** 		&(sdl->window.width), &(sdl->window.height)) ||
** 		sdl->window.window <= 0 || sdl->window.height <= 0)
** 	{
** 		SDL_DestroyRenderer(sdl->window.renderer);
** 		SDL_DestroyWindow(sdl->window.window);
** 		SDL_Quit();
** 		return (print_error_and_return("SDL_GetRendererOutputSize Error"));
** 	}
** 	return (0);
** }
*/

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

int				init(t_sdl *sdl)
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
	return (0);
}
