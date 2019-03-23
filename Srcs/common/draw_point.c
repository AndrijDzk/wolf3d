/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_point.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 14:24:24 by adzikovs          #+#    #+#             */
/*   Updated: 2018/11/07 14:44:00 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common_typedefs.h"

int			draw_point(t_sdl *sdl, SDL_Color *c, int x, int y)
{
	int			line_width;
	int			start;
	int			offset;
	uint32_t	*pixel;

	line_width = sdl->window.surface->w *
		sdl->window.surface->format->BytesPerPixel;
	start = y * line_width;
	offset = x * sdl->window.surface->format->BytesPerPixel;
	pixel = (uint32_t*)((char*)sdl->window.surface->pixels + start + offset);
	*pixel = SDL_MapRGBA(sdl->window.surface->format, c->r, c->g, c->b, c->a);
	return (0);
}

int			check_and_draw_point(t_sdl *sdl, SDL_Color *c, int x, int y)
{
	int			line_width;
	int			start;
	int			offset;
	uint32_t	*pixel;

	line_width = sdl->window.surface->w *
		sdl->window.surface->format->BytesPerPixel;
	start = y * line_width;
	offset = x * sdl->window.surface->format->BytesPerPixel;
	pixel = (uint32_t*)((char*)sdl->window.surface->pixels + start + offset);
	if (*pixel)
		return (0);
	*pixel = SDL_MapRGBA(sdl->window.surface->format, c->r, c->g, c->b, c->a);
	return (0);
}
