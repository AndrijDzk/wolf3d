/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_texture_multithreaded.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 10:16:09 by adzikovs          #+#    #+#             */
/*   Updated: 2018/11/23 10:34:01 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>

#include "common.h"

#include "math_3d.h"

#include "rasterization.h"

#define THREADS_AM 4

static int	adjust_y_to_window_height(const SDL_Surface *window,
				int *y_start, int *y_end)
{
	if (*y_start < 0)
		*y_start = 0;
	else if (*y_start > window->h)
		*y_start = window->h;
	if (*y_end < 0)
		*y_end = 0;
	else if (*y_end > window->h)
		*y_end = window->h;
	if (*y_end <= *y_start)
		return (1);
	return (0);
}

static void	init_slave_params(t_drt_slave_param params[THREADS_AM],
				t_borders_table *borders,
				t_xpm_texture *texture,
				t_sdl *sdl)
{
	int		i;
	int		y_start;
	int		y_end;
	int		length_thread;

	y_start = params[0].y_start;
	y_end = params[0].y_end;
	length_thread = (y_end - y_start) / THREADS_AM;
	i = 0;
	while (i < THREADS_AM)
	{
		params[i].y_start = y_start + length_thread * i;
		params[i].y_end = y_start + length_thread * (i + 1);
		params[i].sdl = sdl;
		params[i].borders = borders;
		params[i].txt = texture;
		i++;
	}
	params[THREADS_AM - 1].y_end = y_end;
}

static void	drawing(t_drt_slave_param params[THREADS_AM])
{
	pthread_t	slaves[THREADS_AM];
	size_t		i;

	i = 0;
	while (i < THREADS_AM)
	{
		if (pthread_create(slaves + i, NULL,
			draw_texture_multithreaded_slave, params + i))
			break ;
		i++;
	}
	while (i > 0)
	{
		i--;
		pthread_join(slaves[i], NULL);
	}
}

int			draw_texture_multithreaded(char order, t_sdl *sdl,
				t_textured_2d_segment *segments[5],
				t_xpm_texture *txt)
{
	t_textured_2d_segment	*borders[2][5];
	t_drt_slave_param		params[THREADS_AM];

	ft_bzero(borders, sizeof(**borders) * 10);
	if (get_left_and_right_borders(segments, order, borders[0], borders[1]) ||
		get_border_min_and_max_y(borders[0],
			&params[0].y_start, &params[0].y_end))
		return (1);
	if (adjust_y_to_window_height(sdl->window.surface,
		&params[0].y_start, &params[0].y_end))
		return (1);
	init_slave_params(params, &borders, txt, sdl);
	drawing(params);
	return (0);
}
