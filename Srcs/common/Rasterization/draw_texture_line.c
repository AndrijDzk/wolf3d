/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_texture_line.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 10:02:52 by adzikovs          #+#    #+#             */
/*   Updated: 2018/11/23 12:20:48 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rasterization.h"

#include "common.h"

static void	init_error_color(SDL_Color *c)
{
	ft_bzero(c, sizeof(*c));
	c->b = 255;
}

static void	draw_texture_line_init(
				t_sdl *sdl,
				int x[4],
				double txt_crd[3],
				t_texturing_data *line)
{
	x[0] = (int)round(line->bounds[0] - DBL_ZERO);
	x[1] = (int)round(line->bounds[1]) + 1;
	if (x[1] >= sdl->window.surface->w)
		x[1] = sdl->window.surface->w;
	if (x[0] >= 0)
	{
		txt_crd[0] = line->x_z[0];
		txt_crd[1] = line->y_z[0];
		txt_crd[2] = line->one_z[0];
	}
	else
	{
		txt_crd[0] = line->x_z[0] - x[0] * line->x_z[1];
		txt_crd[1] = line->y_z[0] - x[0] * line->y_z[1];
		txt_crd[2] = line->one_z[0] - x[0] * line->one_z[1];
		x[0] = 0;
	}
}

static void	draw_texture_line_init2(
				t_list *occupied,
				int x[4],
				double txt_crd[3],
				t_texturing_data *line)
{
	t_list		*tmp;
	int			diff;

	tmp = find_occupied_segment(occupied, x[0]);
	if (tmp)
	{
		diff = ((int*)tmp->data)[1] + 1 - x[0];
		x[0] += diff;
		txt_crd[0] += diff * line->x_z[1];
		txt_crd[1] += diff * line->y_z[1];
		txt_crd[2] += diff * line->one_z[1];
	}
	x[2] = x[0];
	x[3] = find_next_first_occupied_point(x[0], occupied);
}

static void	increment_crd(int x[4], double t_crd[3], t_texturing_data *line)
{
	t_crd[0] += line->x_z[1];
	t_crd[1] += line->y_z[1];
	t_crd[2] += line->one_z[1];
	x[0]++;
}

void		draw_texture_line(t_sdl *sdl, t_xpm_texture *txt, int y,
				t_texturing_data *line)
{
	int			x[4];
	double		t_crd[3];
	SDL_Color	*color;
	SDL_Color	tmp;

	init_error_color(&tmp);
	draw_texture_line_init(sdl, x, t_crd, line);
	draw_texture_line_init2(sdl->window.screen_data[y], x, t_crd, line);
	while (x[0] < x[1])
	{
		if (x[0] >= x[3])
			move_to_the_end_of_occupied_segment(x, t_crd, line,
				sdl->window.screen_data[y]);
		else
		{
			color = get_point_from_xpm_texture(
				t_crd[0] / t_crd[2], t_crd[1] / t_crd[2], txt);
			if (color)
				draw_point(sdl, color, x[0], y);
			else
				draw_point(sdl, &tmp, x[0], y);
			increment_crd(x, t_crd, line);
		}
	}
	add_new_occupied_segment(sdl->window.screen_data + y, x);
}
