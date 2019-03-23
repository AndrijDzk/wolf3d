/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/25 11:18:41 by adzikovs          #+#    #+#             */
/*   Updated: 2018/10/26 12:18:38 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "common.h"

static int		draw_horizontal(t_sdl *sdl, t_vec2d *start, t_vec2d *end,
					SDL_Color *color)
{
	double		coeff;
	int			x;
	double		y;
	int			yr;

	coeff = (end->y - start->y) / (end->x - start->x);
	x = (int)round(start->x);
	end->x = round(end->x);
	while (x <= end->x)
	{
		y = coeff * x - coeff * start->x + start->y;
		yr = (int)round(y);
		if (x >= 0 && yr >= 0 &&
			x < sdl->window.surface->w &&
			yr < sdl->window.surface->h)
			check_and_draw_point(sdl, color, x, yr);
		x++;
	}
	return (0);
}

static int		draw_vertical(t_sdl *sdl, t_vec2d *start, t_vec2d *end,
					SDL_Color *color)
{
	double		coeff;
	int			y;
	double		x;
	int			xr;

	coeff = (end->x - start->x) / (end->y - start->y);
	y = (int)round(start->y);
	end->y = round(end->y);
	while (y <= end->y)
	{
		x = coeff * y - coeff * start->y + start->x;
		xr = (int)round(x);
		if (xr >= 0 && y >= 0 &&
			xr < sdl->window.surface->w &&
			y < sdl->window.surface->h)
			check_and_draw_point(sdl, color, xr, y);
		y++;
	}
	return (0);
}

int				draw_line(t_sdl *sdl, t_vec2d *start, t_vec2d *end,
					SDL_Color *color)
{
	if (fabs(start->x - end->x) > fabs(start->y - end->y))
	{
		if (start->x < end->x)
			draw_horizontal(sdl, start, end, color);
		else
			draw_horizontal(sdl, end, start, color);
	}
	else
	{
		if (start->y < end->y)
			draw_vertical(sdl, start, end, color);
		else
			draw_vertical(sdl, end, start, color);
	}
	return (0);
}

/*
** static int		rectangle_draw_horizontal(t_sdl *sdl,
** 					t_vec3d vertex[4], SDL_Color *color)
** {
** 	double		coeff1;
** 	double		coeff2;
** 	t_vec2d		s;
** 	t_vec2d		e;
**
** 	coeff1 = (vertex[1].y - vertex[0].y) / (vertex[1].x - vertex[0].x);
** 	coeff2 = (vertex[2].y - vertex[3].y) / (vertex[2].x - vertex[3].x);
** 	s.x = vertex[0].x;
** 	e.x = vertex[3].x;
** 	while (s.x <= vertex[1].x && e.x <= vertex[2].x)
** 	{
** 		s.y = coeff1 * s.x - coeff1 * vertex[0].x + vertex[0].y;
** 		e.y = coeff2 * s.x - coeff2 * vertex[3].x + vertex[3].y;
** 		draw_line(sdl, &s, &e, color);
** 		s.x += 1;
** 		e.x += 1;
** 	}
** 	return (0);
** }
**
** static int		rectangle_draw_vertical(t_sdl *sdl,
** 					t_vec3d vertex[4], SDL_Color *color)
** {
** 	double		coeff1;
** 	double		coeff2;
** 	t_vec2d		s;
** 	t_vec2d		e;
**
** 	coeff1 = (vertex[1].x - vertex[0].x) / (vertex[1].y - vertex[0].y);
** 	coeff2 = (vertex[2].x - vertex[3].x) / (vertex[2].y - vertex[3].y);
** 	s.y = vertex[0].y;
** 	e.y = vertex[3].y;
** 	while (s.y <= vertex[1].y && e.y <= vertex[2].y)
** 	{
** 		if (fabs(s.y - 384) < 1)
** 			ft_printf("Gotcha!\n");
** 		s.x = coeff1 * s.y - coeff1 * vertex[0].y + vertex[0].x;
** 		e.x = coeff2 * s.y - coeff2 * vertex[3].y + vertex[3].x;
** 		draw_line(sdl, &s, &e, color);
** 		s.y += 1;
** 		e.y += 1;
** 	}
** 	return (0);
** }
**
** void			t_vec3d_swap(t_vec3d *v1, t_vec3d *v2)
** {
** 	t_vec3d		tmp;
**
** 	tmp = *v1;
** 	*v1 = *v2;
** 	*v2 = tmp;
** }
**
** int				draw_rectangle(t_sdl *sdl, t_vec3d vertex[4],
** 					SDL_Color *color)
** {
** 	t_vec3d		*v0;
** 	t_vec3d		*v1;
** 	t_vec3d		*v2;
** 	t_vec3d		*v3;
**
** 	v0 = vertex;
** 	v1 = vertex + 1;
** 	v2 = vertex + 2;
** 	v3 = vertex + 3;
** 	if (fabs(vertex[0].x - vertex[1].x) > fabs(vertex[0].y - vertex[1].y))
** 	{
** 		if (vertex[0].x < vertex[1].x)
** 			rectangle_draw_horizontal(sdl, vertex, color);
** 		else
** 		{
** 			t_vec3d_swap(vertex, vertex + 1);
** 			t_vec3d_swap(vertex + 2, vertex + 3);
** 			rectangle_draw_horizontal(sdl, vertex, color);
** 		}
** 	}
** 	else
** 	{
** 		if (vertex[0].y < vertex[1].y)
** 			rectangle_draw_vertical(sdl, vertex, color);
** 		else
** 		{
** 			t_vec3d_swap(vertex, vertex + 1);
** 			t_vec3d_swap(vertex + 2, vertex + 3);
** 			rectangle_draw_vertical(sdl, vertex, color);
** 		}
** 	}
** 	return (0);
** }
*/
