/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_border_min_and_max_y.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/10 13:08:20 by adzikovs          #+#    #+#             */
/*   Updated: 2018/11/13 10:08:37 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common_typedefs.h"

static void	update_res(
				const t_textured_2d_segment *segment,
				int *res_min,
				int *res_max)
{
	if (res_min)
	{
		if (segment->segment.y[0] < *res_min)
			*res_min = (int)round(segment->segment.y[0] - DBL_ZERO);
		if (segment->segment.y[1] < *res_min)
			*res_min = (int)round(segment->segment.y[1] - DBL_ZERO);
	}
	if (res_max)
	{
		if (segment->segment.y[0] > *res_max)
			*res_max = (int)round(segment->segment.y[0]);
		if (segment->segment.y[1] > *res_max)
			*res_max = (int)round(segment->segment.y[1]);
	}
}

static void	init_res(
				const t_textured_2d_segment *segment,
				int *res_min,
				int *res_max)
{
	if (segment->segment.y[0] < segment->segment.y[1])
	{
		if (res_min)
			*res_min = (int)round(segment->segment.y[0] - DBL_ZERO);
		if (res_max)
			*res_max = (int)round(segment->segment.y[1]);
	}
	else
	{
		if (res_min)
			*res_min = (int)round(segment->segment.y[1] - DBL_ZERO);
		if (res_max)
			*res_max = (int)round(segment->segment.y[0]);
	}
}

int			get_border_min_and_max_y(
				t_textured_2d_segment *segments[5],
				int *res_min,
				int *res_max)
{
	size_t	i;

	i = 0;
	while (segments[i] == NULL && i < 5)
		i++;
	if (i >= 5)
		return (1);
	init_res(segments[i], res_min, res_max);
	while (i < 5)
	{
		if (segments[i])
			update_res(segments[i], res_min, res_max);
		i++;
	}
	return (0);
}
