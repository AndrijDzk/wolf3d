/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_vertexes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 15:39:07 by adzikovs          #+#    #+#             */
/*   Updated: 2018/11/05 16:14:39 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common_typedefs.h"

static int	rasterization_get_vert_surface_vertexes(
				const t_surface *surface,
				t_vec3d vertexes[4])
{
	vertexes[0] = surface->plane.pos;
	vertexes[1] = vertexes[0];
	vertexes[1].y += surface->height;
	vertexes[2] = vertexes[1];
	vertexes[2].x += surface->length * surface->plane.norm.z;
	vertexes[2].z -= surface->length * surface->plane.norm.x;
	vertexes[3] = vertexes[2];
	vertexes[3].y -= surface->height;
	return (0);
}

static int	rasterization_get_hor_surface_vertexes(
				const t_surface *surface,
				t_vec3d vertexes[4])
{
	char	order;

	if (surface->plane.norm.y > 0)
		order = 1;
	else if (surface->plane.norm.y < 0)
		order = -1;
	else
		return (1);
	vertexes[0] = surface->plane.pos;
	vertexes[1] = vertexes[0];
	vertexes[1].x += surface->length;
	vertexes[2] = vertexes[1];
	vertexes[2].z += surface->height * order;
	vertexes[3] = vertexes[2];
	vertexes[3].x -= surface->length;
	return (0);
}

int			rasterization_get_vertex_crd(const t_surface *surface,
				t_vec3d vertexes[4])
{
	if (fabs(surface->plane.norm.y) <= DBL_ZERO)
		return (rasterization_get_vert_surface_vertexes(
					surface,
					vertexes));
	else
		return (rasterization_get_hor_surface_vertexes(
					surface,
					vertexes));
}
