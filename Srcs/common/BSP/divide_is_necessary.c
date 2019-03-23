/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   divide_is_necessary.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 12:13:24 by adzikovs          #+#    #+#             */
/*   Updated: 2018/11/03 10:07:19 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "intersections.h"

#include "common.h"

static int	check_intersection_point(const t_surface *surface, const t_ray *div)
{
	double			x[2];
	double			y[2];
	double			z[2];
	const t_vec3d	*p;

	p = &div->pos;
	x[0] = surface->plane.pos.x;
	y[0] = surface->plane.pos.y;
	z[0] = surface->plane.pos.z;
	x[1] = surface->plane.pos.x + surface->length * surface->plane.norm.z;
	y[1] = surface->plane.pos.y + surface->height;
	z[1] = surface->plane.pos.z - surface->length * surface->plane.norm.x;
	if (fabs(div->dir.y) > DBL_ZERO)
	{
		if ((fabs(p->x - x[0]) <= DBL_ZERO &&
			fabs(p->z - z[0]) <= DBL_ZERO) ||
			(fabs(p->x - x[1]) <= DBL_ZERO &&
			fabs(p->z - z[1]) <= DBL_ZERO))
			return (0);
		else
			return (1);
	}
	else
		return (fabs(y[0] - div->pos.y) > DBL_ZERO &&
			fabs(y[1] - div->pos.y) > DBL_ZERO);
}

int			bsp_divide_is_necessary(const t_surface *base_surface,
				const t_surface *surface, t_ray *div)
{
	t_ray		div_tmp;

	if (base_surface == NULL || surface == NULL)
		return (0);
	if (fabs(surface->plane.norm.y) > DBL_ZERO)
	{
		if (fabs(base_surface->plane.norm.y) <= DBL_ZERO)
			ft_printf("%$bsp_divide_is_necessary: Error: "
				"trying to divide horizontal surface!\n", 2);
		return (0);
	}
	if (surfaces_intersection(base_surface, surface, &div_tmp.pos) == 0)
		return (0);
	if (fabs(base_surface->plane.norm.y) > DBL_ZERO)
		div_tmp.dir.y = 0;
	else
		div_tmp.dir.y = 1;
	if (div)
		ft_memcpy(div, &div_tmp, sizeof(*div));
	return (check_intersection_point(surface, &div_tmp));
}
