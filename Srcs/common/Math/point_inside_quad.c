/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point_inside_quad.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 10:29:51 by adzikovs          #+#    #+#             */
/*   Updated: 2018/11/07 10:29:51 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common_typedefs.h"

static double	point_pos_rel_to_line(
					const t_2d_segment *line,
					const t_vec2d *point)
{
	return (line->a * point->y + line->b * point->x + line->c);
}

int				point_pos_rel_to_quad(
					const t_2d_segment quad[4],
					const t_vec2d *p)
{
	int			ret;
	double		rel_pos;
	size_t		i;

	if (quad == NULL || p == NULL)
		return (0);
	i = 0;
	while (i < 4 &&
			fabs((rel_pos = point_pos_rel_to_line(quad + i, p))) <= DBL_ZERO)
		i++;
	if (i == 4)
		return (1);
	if (rel_pos > 0)
		ret = 1;
	else
		ret = -1;
	while (i < 4)
	{
		rel_pos = point_pos_rel_to_line(quad + i, p);
		if ((rel_pos >= -DBL_ZERO) != (ret >= 0))
			return (0);
		i++;
	}
	return (ret);
}
