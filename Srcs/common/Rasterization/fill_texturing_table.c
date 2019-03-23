/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_texturing_table.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 10:10:07 by adzikovs          #+#    #+#             */
/*   Updated: 2018/11/21 13:39:49 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math_3d.h"

#include "rasterization.h"

#include "common.h"

int		fill_entry_with_left_border_data(int y, t_texturing_data *res,
			t_textured_2d_segment *left_border)
{
	double		a;
	double		b;
	double		c;

	a = left_border->segment.a;
	b = left_border->segment.b;
	c = left_border->segment.c;
	res->bounds[0] = (c - a * (y + 0.5)) / b;
	a = y + 0.5 - left_border->segment.y[0];
	res->x_z[0] = left_border->data.x_z[0] + a * left_border->data.x_z[1];
	res->y_z[0] = left_border->data.y_z[0] + a * left_border->data.y_z[1];
	res->one_z[0] = left_border->data.one_z[0] + a * left_border->data.one_z[1];
	return (0);
}

int		fill_entry_with_right_border_data(int y, t_texturing_data *res,
			t_textured_2d_segment *right_border)
{
	double		a;
	double		b;
	double		c;

	a = right_border->segment.a;
	b = right_border->segment.b;
	c = right_border->segment.c;
	res->bounds[1] = (c - a * (y + 0.5)) / b + 1;
	a = y + 0.5 - right_border->segment.y[0];
	res->x_z[1] = right_border->data.x_z[0] + a * right_border->data.x_z[1];
	res->y_z[1] = right_border->data.y_z[0] + a * right_border->data.y_z[1];
	res->one_z[1] = right_border->data.one_z[0] +
		a * right_border->data.one_z[1];
	return (0);
}

int		find_borders_for_y(
			double y,
			t_textured_2d_segment *borders[2][5],
			t_textured_2d_segment **res_left,
			t_textured_2d_segment **res_right)
{
	size_t		i;

	y += 0.5;
	*res_left = NULL;
	i = 0;
	while (i < 5)
	{
		if (borders[0][i] && check_limits_inclusive(
			borders[0][i]->segment.y[0], borders[0][i]->segment.y[1], y))
			*res_left = borders[0][i];
		i++;
	}
	*res_right = NULL;
	i = 0;
	while (i < 5)
	{
		if (borders[1][i] && check_limits_inclusive(
			borders[1][i]->segment.y[0], borders[1][i]->segment.y[1], y))
			*res_right = borders[1][i];
		i++;
	}
	if (*res_left == NULL || *res_right == NULL)
		return (1);
	return (0);
}

int		fill_texturing_table(
			t_texturing_table *res,
			t_textured_2d_segment *borders[2][5])
{
	int						y;
	size_t					i;
	t_textured_2d_segment	*left_border;
	t_textured_2d_segment	*right_border;

	res->rows = (t_texturing_data*)malloc(sizeof(*res->rows) *
		(res->y_end - res->y_start));
	i = 0;
	y = res->y_start;
	while (y < res->y_end)
	{
		if (find_borders_for_y(y, borders, &left_border, &right_border))
		{
			free(res->rows);
			return (1);
		}
		fill_entry_with_left_border_data(y, res->rows + i, left_border);
		fill_entry_with_right_border_data(y, res->rows + i, right_border);
		approximate_texturing_data_along_line(res->rows + i);
		i++;
		y++;
	}
	return (0);
}
