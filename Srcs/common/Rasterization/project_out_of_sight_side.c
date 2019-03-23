/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   project_out_of_sight_side.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 11:48:46 by adzikovs          #+#    #+#             */
/*   Updated: 2018/11/18 10:55:07 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math_3d.h"

int			check_for_out_of_sight_side(t_vec3d vertexes[5][2])
{
	size_t	i;
	char	vis;
	char	invis;

	vis = 0;
	invis = 0;
	i = 0;
	while (i < 4)
	{
		if (vertexes[i][0].z >= 0)
			invis = 1;
		else
			vis = 1;
		i++;
	}
	if (vis & invis)
		return (1);
	else
		return (0);
}

static int	find_out_of_sight_boundaries(
				t_vec3d vertexes[5][2],
				size_t res[2])
{
	size_t	i;

	if (check_for_out_of_sight_side(vertexes) == 0)
		return (1);
	i = 0;
	while (vertexes[i][0].z < 0 && i < 4)
		i++;
	if (i == 4)
		return (1);
	res[0] = i;
	while (vertexes[res[0]][0].z >= 0)
		res[0] = (res[0] + 4 - 1) % 4;
	res[1] = i;
	while (vertexes[(res[1] + 1) % 4][0].z >= 0)
		res[1] = (res[1] + 1) % 4;
	return (0);
}

int			project_out_of_sight_side(
				t_vec3d vertexes[5][2],
				t_textured_2d_segment *res_ptrs[5])
{
	size_t s[2];

	if (find_out_of_sight_boundaries(vertexes, s))
	{
		res_ptrs[4] = NULL;
		return (1);
	}
	build_line(&vertexes[4][1], &vertexes[4][0], &res_ptrs[4]->segment, NULL);
	(res_ptrs[4])->data.x_z[0] = res_ptrs[s[0]]->data.x_z[1];
	(res_ptrs[4])->data.y_z[0] = res_ptrs[s[0]]->data.y_z[1];
	(res_ptrs[4])->data.one_z[0] = res_ptrs[s[0]]->data.one_z[1];
	(res_ptrs[4])->data.x_z[1] = res_ptrs[s[1]]->data.x_z[0];
	(res_ptrs[4])->data.y_z[1] = res_ptrs[s[1]]->data.y_z[0];
	(res_ptrs[4])->data.one_z[1] = res_ptrs[s[1]]->data.one_z[0];
	return (0);
}
