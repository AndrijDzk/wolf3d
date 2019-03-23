/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_lines_from_vertexes.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 15:22:47 by adzikovs          #+#    #+#             */
/*   Updated: 2018/11/18 10:49:47 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common_typedefs.h"

int		build_line(
			const t_vec3d *v1,
			const t_vec3d *v2,
			t_2d_segment *res,
			t_2d_segment **res_ptr)
{
	if (v1 == NULL || v2 == NULL || res == NULL)
		return (1);
	res->x[0] = v1->x;
	res->y[0] = v1->y;
	res->x[1] = v2->x;
	res->y[1] = v2->y;
	res->a = res->x[1] - res->x[0];
	res->b = res->y[0] - res->y[1];
	res->c = +res->y[0] * res->a + res->x[0] * res->b;
	if (res_ptr)
		*res_ptr = res;
	return (0);
}

int		build_lines(t_vec3d *vertex[9],
			t_2d_segment res[8], t_2d_segment *res_ptr[8])
{
	size_t			i;

	i = 0;
	while (i < 7 && vertex[i + 1])
	{
		build_line(vertex[i], vertex[i + 1], res + i, res_ptr + i);
		i++;
	}
	if (i == 0)
		return (1);
	build_line(vertex[i], vertex[0], res + i, res_ptr + i);
	return (0);
}
