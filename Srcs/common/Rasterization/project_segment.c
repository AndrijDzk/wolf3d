/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   project_segment.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/11 14:17:54 by adzikovs          #+#    #+#             */
/*   Updated: 2018/11/15 11:03:16 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common_defines.h"

#include "math_3d.h"

#include "rasterization.h"

static void	aproximate_intersection_crd(
				const t_vec3d *out_of_sight,
				const t_vec3d *end,
				double *coeff,
				t_vec3d *res)
{
	double	aprox_z;

	if (end->z < -0.1)
		aprox_z = -0.1;
	else
		aprox_z = end->z / 20;
	*coeff = (out_of_sight->z - aprox_z) / (out_of_sight->z - end->z);
	res->x = out_of_sight->x + (end->x - out_of_sight->x) * *coeff;
	res->y = out_of_sight->y + (end->y - out_of_sight->y) * *coeff;
	res->z = aprox_z;
}

static void	approximate_start(
				t_camera *camera,
				t_vec3d seg[5][2],
				t_textured_2d_segment *res,
				unsigned i)
{
	double		coeff;
	unsigned	next;

	next = (i + 1) % 4;
	aproximate_intersection_crd(&seg[i][0], &seg[next][0], &coeff, &seg[4][0]);
	project_vertex_on_screen(camera, &seg[4][0]);
	build_line(&seg[4][0], &seg[next][1], &res->segment, NULL);
	init_texture_crd(APPROXIMATE_FIRST, coeff, i, &res->data);
	res->data.one_z[0] = 1 / seg[4][0].z;
	res->data.one_z[1] = 1 / seg[next][1].z;
}

static void	approximate_end(
				t_camera *camera,
				t_vec3d seg[5][2],
				t_textured_2d_segment *res,
				unsigned i)
{
	double		coeff;
	unsigned	next;

	next = (i + 1) % 4;
	aproximate_intersection_crd(&seg[next][0], &seg[i][0], &coeff, &seg[4][1]);
	project_vertex_on_screen(camera, &seg[4][1]);
	build_line(&seg[i][1], &seg[4][1], &res->segment, NULL);
	init_texture_crd(APPROXIMATE_SECOND, coeff, i, &res->data);
	res->data.one_z[0] = 1 / seg[i][1].z;
	res->data.one_z[1] = 1 / seg[4][1].z;
}

int			project_segment(
				t_camera *camera,
				t_vec3d segment[5][2],
				t_textured_2d_segment *res,
				unsigned i)
{
	unsigned	next;

	next = (i + 1) % 4;
	if (segment[i][1].z >= 0 && segment[next][1].z >= 0)
		return (1);
	else if (segment[i][1].z >= 0)
		approximate_start(camera, segment, res, i);
	else if (segment[next][1].z >= 0)
		approximate_end(camera, segment, res, i);
	else
	{
		build_line(&segment[i][1], &segment[next][1], &res->segment, NULL);
		init_texture_crd(DOSENT_APROXIMATE, 0, i, &res->data);
		res->data.one_z[0] = 1 / segment[i][1].z;
		res->data.one_z[1] = 1 / segment[next][1].z;
	}
	return (0);
}
