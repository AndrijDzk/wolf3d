/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_texture_projection.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/03 09:55:03 by adzikovs          #+#    #+#             */
/*   Updated: 2018/11/24 10:30:44 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "return_codes.h"

#include "common_defines.h"

#include "rasterization.h"

#include "common.h"

static void	prepare_texturing_data_for_segment(t_textured_2d_segment *res)
{
	res->data.bounds[0] = res->segment.y[0];
	res->data.bounds[1] = res->segment.y[1];
	res->data.x_z[0] *= res->data.one_z[0];
	res->data.y_z[0] *= res->data.one_z[0];
	res->data.x_z[1] *= res->data.one_z[1];
	res->data.y_z[1] *= res->data.one_z[1];
	approximate_texturing_data_along_line(&res->data);
}

static void	prepare_texturing_data(t_textured_2d_segment *res[4])
{
	size_t	i;

	i = 0;
	while (i < 5)
	{
		if (res[i])
		{
			if ((res[i]->segment.y[1] - res[i]->segment.y[0]) != 0)
				prepare_texturing_data_for_segment(res[i]);
			else
				res[i] = NULL;
		}
		i++;
	}
}

void		project_vertex_on_screen(t_camera *camera, t_vec3d *v)
{
	perspective_divide(v, &camera->focal_length);
	v->x += (double)camera->w / 2;
	v->y = (double)camera->h / 2 - v->y;
}

void		get_texture_projection(
				t_camera *camera,
				t_vec3d vertexes[4],
				t_textured_2d_segment *res_ptrs[5])
{
	unsigned	i;
	t_vec3d		proj_vertexes[5][2];

	i = 0;
	while (i < 4)
	{
		ft_memcpy(proj_vertexes[i], vertexes + i, sizeof(*vertexes));
		ft_memcpy(proj_vertexes[i] + 1, vertexes + i, sizeof(*vertexes));
		if (proj_vertexes[i][0].z < 0)
			project_vertex_on_screen(camera, proj_vertexes[i] + 1);
		i++;
	}
	i = 0;
	while (i < 4)
	{
		if (project_segment(camera, proj_vertexes, res_ptrs[i], i))
			res_ptrs[i] = NULL;
		i++;
	}
	project_out_of_sight_side(proj_vertexes, res_ptrs);
	prepare_texturing_data(res_ptrs);
}
