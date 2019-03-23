/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_texturing_data.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/10 10:00:02 by adzikovs          #+#    #+#             */
/*   Updated: 2018/11/13 10:16:27 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math_3d.h"

#include "rasterization.h"

#include "common.h"

/*
**static void			conditional_swap(
**						t_2d_segment **s1,
**						t_2d_segment **s2)
**{
**	t_2d_segment	*tmp;
**
**	if ((*s1)->y[0] > (*s2)->y[0])
**	{
**		tmp = *s1;
**		*s1 = *s2;
**		*s2 = tmp;
**	}
**}
**
**static int			sort_segments(t_2d_segment *segments[5])
**{
**	size_t			i;
**	size_t			j;
**
**	i = 0;
**	while (i < 5 && segments[i])
**	{
**		j = 0;
**		while (j < (4 - i) && segments[j])
**		{
**			conditional_swap(segments + j, segments + j + 1);
**			j++;
**		}
**		i++;
**	}
**	return (0);
**}
*/

static void					adjust_y_to_window_height(const SDL_Surface *window,
								t_texturing_table *res)
{
	if (res->y_start < 0)
		res->y_start = 0;
	else if (res->y_start > window->h)
		res->y_start = window->h;
	if (res->y_end < 0)
		res->y_end = 0;
	else if (res->y_end > window->h)
		res->y_end = window->h;
}

static t_texturing_table	*calculate_texturing_data_error_exit(
								t_texturing_table *res)
{
	free(res);
	return (NULL);
}

t_texturing_table			*calculate_texturing_data(
								char order, t_sdl *sdl,
								t_textured_2d_segment *segments[5])
{
	t_texturing_table		*res;
	t_textured_2d_segment	*borders[2][5];

	ft_bzero(borders, sizeof(**borders) * 10);
	res = (t_texturing_table*)malloc(sizeof(*res));
	if (get_left_and_right_borders(segments, order, borders[0], borders[1]) ||
		get_border_min_and_max_y(borders[0], &res->y_start, &res->y_end))
		return (calculate_texturing_data_error_exit(res));
	adjust_y_to_window_height(sdl->window.surface, res);
	if (res->y_end <= res->y_start)
		return (calculate_texturing_data_error_exit(res));
	if (fill_texturing_table(res, borders))
		return (calculate_texturing_data_error_exit(res));
	return (res);
}
