/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_vertex_projections.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/03 09:55:03 by adzikovs          #+#    #+#             */
/*   Updated: 2018/11/11 14:54:49 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "return_codes.h"

#include "rasterization.h"

#include "common.h"

/*
**static void	aproximate_intersection_crd(
**				const t_vec3d *out_of_sight,
**				const t_vec3d *end,
**				t_vec3d *res)
**{
**	double	coeff;
**	double	aprox_z;
**
**	if (end->z < -0.1)
**		aprox_z = -0.1;
**	else
**		aprox_z = end->z / 20;
**	coeff = (out_of_sight->z - aprox_z) / (out_of_sight->z - end->z);
**	res->x = out_of_sight->x + (end->x - out_of_sight->x) * coeff;
**	res->y = out_of_sight->y + (end->y - out_of_sight->y) * coeff;
**	res->z = aprox_z;
**}
**
**static int	get_segment_projection(t_vec3d segment[2],
**				t_vec3d proj_data[2],
**				t_vec3d *proj_pointers[2],
**				char proceed_start)
**{
**	if (segment[0].z >= 0 && segment[1].z >= 0)
**		return (WTF);
**	if (proceed_start)
**	{
**		if (segment[0].z >= 0)
**			aproximate_intersection_crd(segment, segment + 1, proj_data);
**		else
**			ft_memcpy(proj_data, segment, sizeof(*segment));
**		perspective_divide(proj_data);
**		proj_pointers[0] = proj_data;
**	}
**	if (segment[1].z >= 0)
**		aproximate_intersection_crd(segment + 1, segment, proj_data + 1);
**	else
**		ft_memcpy(proj_data + 1, segment + 1, sizeof(*segment));
**	perspective_divide(proj_data + 1);
**	proj_pointers[1] = proj_data + 1;
**	return (0);
**}
**
**static int	project_last_segment(
**				t_vec3d vertexes[4],
**				t_vec3d proj_data[8],
**				t_vec3d *proj_pointers[8],
**				size_t ct)
**{
**	t_vec3d	seg_tmp[2];
**
**	seg_tmp[0] = vertexes[3];
**	seg_tmp[1] = vertexes[0];
**	if (vertexes[3].z >= 0)
**		get_segment_projection(seg_tmp, proj_data + ct, proj_pointers + ct, 1);
**	else if (vertexes[0].z >= 0)
**	{
**		ct--;
**		get_segment_projection(seg_tmp, proj_data + ct, proj_pointers + ct, 0);
**	}
**	if (vertexes[0].z < 0)
**		proj_pointers[ct + 1] = NULL;
**	return (0);
**}
**
**int			rasterization_get_vertex_projections(
**				t_vec3d vertexes[4],
**				t_vec3d proj_data[8],
**				t_vec3d *proj_pointers[8])
**{
**	size_t	i;
**	size_t	ct;
**
**	ct = 0;
**	i = 0;
**	while (i < 3)
**	{
**		if (vertexes[i].z >= 0 || i == 0)
**			get_segment_projection(vertexes + i,
**				proj_data + ct, proj_pointers + ct, 1);
**		else
**		{
**			ct--;
**			get_segment_projection(vertexes + i,
**					proj_data + ct, proj_pointers + ct, 0);
**		}
**		if (vertexes[i].z < 0 || vertexes[i + 1].z < 0)
**			ct += 2;
**		i++;
**	}
**	return (project_last_segment(vertexes, proj_data, proj_pointers, ct));
**}
*/
