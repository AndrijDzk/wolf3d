/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections_2d.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/21 10:51:16 by adzikovs          #+#    #+#             */
/*   Updated: 2018/11/21 11:45:44 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

#include "math_3d.h"

int				vertical_line_intersection(
					const t_2d_segment *s1,
					const t_2d_segment *s2,
					t_vec2d *res)
{
	if (s1 == NULL || s2 == NULL)
		return (0);
	if ((fabs(s1->b) <= DBL_ZERO && fabs(s2->b) <= DBL_ZERO) ||
		(fabs(s1->a) <= DBL_ZERO && fabs(s2->a) <= DBL_ZERO) ||
		(fabs(s1->a) <= DBL_ZERO && fabs(s1->b) <= DBL_ZERO) ||
		(fabs(s2->a) <= DBL_ZERO && fabs(s2->b) <= DBL_ZERO))
		return (0);
	else
	{
		if (res)
		{
			if (fabs(s1->b) <= DBL_ZERO)
			{
				res->x = s1->c / s1->a;
				res->y = (s2->c - s2->a * res->x) / s2->b;
			}
			else
			{
				res->x = s2->c / s2->a;
				res->y = (s1->c - s1->a * res->x) / s1->b;
			}
		}
		return (1);
	}
}

int				lines_2d_intersection(
					const t_2d_segment *s1,
					const t_2d_segment *s2,
					t_vec2d *res)
{
	double		numerator;
	double		denominator;

	if (s1 == NULL || s2 == NULL)
		return (0);
	if (fabs(s1->b) < DBL_ZERO || fabs(s2->b) < DBL_ZERO)
		return (vertical_line_intersection(s1, s2, res));
	denominator = s1->a / s1->b - s2->a / s2->b;
	if (fabs(denominator) < DBL_ZERO)
		return (0);
	if (res)
	{
		numerator = s1->c / s1->b - s2->c / s2->b;
		res->x = numerator / denominator;
		res->y = (s1->c - s1->a * res->x) / s1->b;
	}
	return (1);
}

int				line_segment_2d_intersection(
					const t_2d_segment *line,
					const t_2d_segment *seg,
					t_vec2d *res)
{
	t_vec2d		res_tmp;

	if (line == NULL || seg == NULL)
		return (0);
	if (lines_2d_intersection(line, seg, &res_tmp) == 0)
		return (0);
	if (check_limits(seg->x[0], seg->x[1], res_tmp.x) == 0)
		return (0);
	if (check_limits(seg->y[0], seg->y[1], res_tmp.y) == 0)
		return (0);
	if (res)
		*res = res_tmp;
	return (1);
}

int				segments_2d_intersection(
					const t_2d_segment *s1,
					const t_2d_segment *s2,
					t_vec2d *res)
{
	t_vec2d		res_tmp;

	if (s1 == NULL || s2 == NULL)
		return (0);
	if (lines_2d_intersection(s1, s2, &res_tmp) == 0)
		return (0);
	if (check_limits(s1->x[0], s1->x[1], res_tmp.x) == 0 ||
		check_limits(s2->x[0], s2->x[1], res_tmp.x) == 0)
		return (0);
	if (check_limits(s1->y[0], s1->y[1], res_tmp.y) == 0 ||
		check_limits(s2->y[0], s2->y[1], res_tmp.y) == 0)
		return (0);
	if (res)
		*res = res_tmp;
	return (1);
}
