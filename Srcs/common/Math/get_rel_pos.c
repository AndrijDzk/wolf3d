/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_rel_pos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/21 12:05:15 by adzikovs          #+#    #+#             */
/*   Updated: 2018/10/21 12:23:39 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_vec3d_math.h"

double			get_surface_point_rel_pos(const t_surface *surface,
					double x, double y, double z)
{
	double	d;
	double	res;

	d = t_vec3d_dot_product(&surface->plane.pos, &surface->plane.norm);
	res = surface->plane.norm.x * x + surface->plane.norm.y * y;
	res += surface->plane.norm.z * z - d;
	return (res);
}

static double	vert_surfaces_rel_pos(const t_surface *base_surface,
					const t_surface *test)
{
	double	rel_pos;
	double	x;
	double	z;

	if (base_surface == NULL || test == NULL ||
		fabs(base_surface->plane.norm.y) > DBL_ZERO ||
		fabs(test->plane.norm.y) > DBL_ZERO)
		return (0);
	rel_pos = get_surface_point_rel_pos(base_surface, test->plane.pos.x,
				test->plane.pos.y, test->plane.pos.z);
	if (fabs(rel_pos) > DBL_ZERO)
		return (rel_pos);
	else
	{
		x = test->plane.pos.x + test->length * test->plane.norm.z;
		z = test->plane.pos.z - test->length * test->plane.norm.x;
		return (get_surface_point_rel_pos(
				base_surface,
				x,
				test->plane.pos.y,
				z));
	}
}

double			get_surface_surface_rel_pos(const t_surface *base_surface,
					const t_surface *test)
{
	if (base_surface == NULL || test == NULL)
		return (0);
	else if (fabs(base_surface->plane.norm.y) <= DBL_ZERO &&
			fabs(test->plane.norm.y) <= DBL_ZERO)
		return (vert_surfaces_rel_pos(base_surface, test));
	else if (fabs(base_surface->plane.pos.y - test->plane.pos.y) <= DBL_ZERO)
		return (0);
	else if (fabs(base_surface->plane.norm.y) > DBL_ZERO)
		return (base_surface->plane.norm.y *
				(test->plane.pos.y - base_surface->plane.pos.y));
	else
		return (test->plane.norm.y *
				(base_surface->plane.pos.y - test->plane.pos.y));
}
