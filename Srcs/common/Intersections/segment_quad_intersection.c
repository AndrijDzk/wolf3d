/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   segment_quad_intersection.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 12:50:57 by adzikovs          #+#    #+#             */
/*   Updated: 2018/11/21 12:59:12 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "math_3d.h"

#include "intersections.h"

int				segment_inside_quad(
					const t_2d_segment quad[4],
					const t_2d_segment *s,
					t_vec2d *res)
{
	t_vec2d		tmp;

	if (quad == NULL || s == NULL)
		return (0);
	tmp.x = s->x[0];
	tmp.y = s->y[0];
	if (point_pos_rel_to_quad(quad, &tmp) > 0)
	{
		if (res)
			*res = tmp;
		return (1);
	}
	tmp.x = s->x[1];
	tmp.y = s->y[1];
	if (point_pos_rel_to_quad(quad, &tmp) > 0)
	{
		if (res)
			*res = tmp;
		return (1);
	}
	return (0);
}

int				segment_lies_on_quad_edge(
					const t_2d_segment quad[4],
					const t_2d_segment *s,
					t_vec2d *res)
{
	size_t		i;
	double		r[3];

	i = 0;
	while (i < 4)
	{
		r[0] = quad[i].a / s->a;
		r[1] = quad[i].b / s->b;
		r[2] = quad[i].c / s->c;
		if (fabs(r[0] - r[1]) <= DBL_ZERO && fabs(r[1] - r[2]) <= DBL_ZERO)
		{
			res->x = quad[i].x[0];
			res->y = quad[i].y[0];
			return (1);
		}
		i++;
	}
	return (0);
}

int				segment_quad_intersection(
					const t_2d_segment quad[4],
					const t_2d_segment *s,
					t_vec2d *res)
{
	if (quad == NULL || s == NULL)
		return (0);
	if (segments_2d_intersection(quad, s, res))
		return (1);
	else if (segments_2d_intersection(quad + 1, s, res))
		return (1);
	else if (segments_2d_intersection(quad + 2, s, res))
		return (1);
	else if (segments_2d_intersection(quad + 3, s, res))
		return (1);
	else
		return (0);
}
