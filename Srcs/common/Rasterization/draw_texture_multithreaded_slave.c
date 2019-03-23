/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_texture_multithreaded_slave.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/18 11:17:52 by adzikovs          #+#    #+#             */
/*   Updated: 2018/11/18 14:16:32 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rasterization.h"

void	draw_texture_multithreaded_slave_body(t_drt_slave_param *param)
{
	int						y;
	t_textured_2d_segment	*left_border;
	t_textured_2d_segment	*right_border;
	t_texturing_data		line;

	y = param->y_start;
	while (y < param->y_end)
	{
		if (find_borders_for_y(y, *param->borders,
			&left_border, &right_border) == 0)
		{
			fill_entry_with_left_border_data(y, &line, left_border);
			fill_entry_with_right_border_data(y, &line, right_border);
			approximate_texturing_data_along_line(&line);
			draw_texture_line(param->sdl, param->txt, y, &line);
		}
		y++;
	}
}

void	*draw_texture_multithreaded_slave(void *param)
{
	draw_texture_multithreaded_slave_body(param);
	return (NULL);
}
