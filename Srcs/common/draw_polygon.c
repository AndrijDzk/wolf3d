/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_polygon.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 13:44:24 by adzikovs          #+#    #+#             */
/*   Updated: 2018/11/11 14:51:44 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

#include "math_3d.h"

double			point_pos_rel_to_line(const t_2d_segment *line,
					double x, double y)
{
	return (line->a * y + line->b * x - line->c);
}

char			point_inside_polygon(
					t_2d_segment *polygon[8],
					int x,
					int y,
					char order)
{
	size_t			i;
	double			rel_pos;

	i = 0;
	while (i < 8 && polygon[i])
	{
		rel_pos = point_pos_rel_to_line(polygon[i], x, y);
		if ((order > 0 && rel_pos < 0) ||
			((order <= 0 && rel_pos > 0)))
			return (0);
		i++;
	}
	return (1);
}

int				draw_polygon(t_sdl *sdl, t_vec3d *vertex[9],
					SDL_Color *color, char order)
{
	int					x;
	int					y;
	t_2d_segment		coefficients[8];
	t_2d_segment		*coeff_ptr[8];
	uint32_t			*pixels;

	ft_bzero(coeff_ptr, sizeof(*coeff_ptr) * 8);
	if (build_lines(vertex, coefficients, coeff_ptr))
		return (1);
	pixels = sdl->window.surface->pixels;
	y = 0;
	while (y < sdl->window.surface->h)
	{
		x = 0;
		while (x < sdl->window.surface->w)
		{
			if (*pixels == 0 && point_inside_polygon(coeff_ptr, x, y, order))
				draw_point(sdl, color, x, y);
			pixels++;
			x++;
		}
		y++;
	}
	return (0);
}
