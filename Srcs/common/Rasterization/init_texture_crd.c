/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_texture_crd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/11 13:04:11 by adzikovs          #+#    #+#             */
/*   Updated: 2018/11/11 14:15:54 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common_defines.h"

#include "common_typedefs.h"

static void		texturing_data_from_vertex_num(unsigned vertex_num,
					t_texturing_data *res, const unsigned field)
{
	vertex_num = vertex_num % 4;
	if (vertex_num == 0)
	{
		res->x_z[field] = 0;
		res->y_z[field] = 0;
	}
	else if (vertex_num == 1)
	{
		res->x_z[field] = 0;
		res->y_z[field] = 1;
	}
	else if (vertex_num == 2)
	{
		res->x_z[field] = 1;
		res->y_z[field] = 1;
	}
	else
	{
		res->x_z[field] = 1;
		res->y_z[field] = 0;
	}
}

int				init_texture_crd(const char flag, const double coeff,
					const unsigned vertex_num, t_texturing_data *res)
{
	texturing_data_from_vertex_num(vertex_num, res, 0);
	if (vertex_num < 3)
		texturing_data_from_vertex_num(vertex_num + 1, res, 1);
	else
		texturing_data_from_vertex_num(0, res, 1);
	if (flag & APPROXIMATE_FIRST)
	{
		res->x_z[0] += (res->x_z[1] - res->x_z[0]) * coeff;
		res->y_z[0] += (res->y_z[1] - res->y_z[0]) * coeff;
	}
	else if (flag & APPROXIMATE_SECOND)
	{
		res->x_z[1] += (res->x_z[0] - res->x_z[1]) * coeff;
		res->y_z[1] += (res->y_z[0] - res->y_z[1]) * coeff;
	}
	return (0);
}
