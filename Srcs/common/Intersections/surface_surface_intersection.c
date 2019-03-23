/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   surface_surface_intersection.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/19 11:24:16 by adzikovs          #+#    #+#             */
/*   Updated: 2018/11/21 12:26:19 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math_3d.h"

#include "intersections.h"

#include "common.h"

int					pos_and_size_into_segment(double pos, double size,
						double *res)
{
	if (res == NULL)
		return (1);
	if (size >= 0)
	{
		res[0] = pos;
		res[1] = res[0] + size;
	}
	else
	{
		res[1] = pos;
		res[0] = res[1] + size;
	}
	return (0);
}

t_2d_segment		surface_into_2d_segment(const t_surface *s)
{
	t_2d_segment	res;

	res.a = s->plane.norm.x;
	res.b = s->plane.norm.z;
	res.c = t_vec3d_dot_product(&s->plane.pos, &s->plane.norm);
	pos_and_size_into_segment(
		s->plane.pos.x,
		s->length * s->plane.norm.z,
		res.x);
	pos_and_size_into_segment(
		s->plane.pos.z,
		-s->length * s->plane.norm.x,
		res.y);
	return (res);
}

char				check_vertical(const t_surface *s1,
						const t_surface *s2)
{
	double			y1_end;
	double			y2_end;

	y1_end = s1->plane.pos.y + s1->height;
	y2_end = s2->plane.pos.y + s2->height;
	if (check_limits(s1->plane.pos.y, y1_end, s2->plane.pos.y) == 0 &&
		check_limits(s1->plane.pos.y, y1_end, y2_end) == 0 &&
		check_limits(s2->plane.pos.y, y2_end, s1->plane.pos.y) == 0 &&
		check_limits(s2->plane.pos.y, y2_end, y1_end) == 0)
		return (0);
	else
		return (1);
}

int					surface_surface_intersection_as_2d_segments(
						const t_surface *base, const t_surface *s2,
						t_vec3d *res)
{
	t_vec2d			res_tmp;
	t_2d_segment	base_line;
	t_2d_segment	seg2;

	if (base == NULL || s2 == NULL)
		return (-1);
	if (fabs(base->plane.norm.y) <= DBL_ZERO &&
		fabs(s2->plane.norm.y) <= DBL_ZERO)
	{
		if (check_vertical(base, s2) == 0)
			return (0);
		base_line = surface_into_2d_segment(base);
		seg2 = surface_into_2d_segment(s2);
		if (line_segment_2d_intersection(&base_line, &seg2, &res_tmp))
		{
			if (res)
			{
				res->x = res_tmp.x;
				res->y = base->plane.pos.y;
				res->z = res_tmp.y;
			}
			return (1);
		}
	}
	return (0);
}

int					surfaces_intersection(
						const t_surface *s1, const t_surface *s2, t_vec3d *res)
{
	if (s1 == NULL || s2 == NULL)
		return (-1);
	if (fabs(s1->plane.norm.y) <= DBL_ZERO &&
		fabs(s2->plane.norm.y) <= DBL_ZERO)
		return (surface_surface_intersection_as_2d_segments(s1, s2, res));
	else if ((fabs(s1->plane.norm.y) > DBL_ZERO) !=
		(fabs(s2->plane.norm.y) > DBL_ZERO))
		return (horizontal_and_vertical_surfaces_intersection(s1, s2, res));
	else
	{
		if (fabs(s1->plane.pos.y - s2->plane.pos.y) > DBL_ZERO)
			return (0);
		else
			return (1);
	}
}
