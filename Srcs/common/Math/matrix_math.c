/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_math.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/12 12:40:21 by adzikovs          #+#    #+#             */
/*   Updated: 2018/10/27 10:37:44 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common_typedefs.h"

t_vec3d		matrix_4x4_mult_t_vec3d(double m[4][4], t_vec3d const *v)
{
	t_vec3d	res;

	res.x = m[0][0] * v->x + m[0][1] * v->y + m[0][2] * v->z + m[0][3];
	res.y = m[1][0] * v->x + m[1][1] * v->y + m[1][2] * v->z + m[1][3];
	res.z = m[2][0] * v->x + m[2][1] * v->y + m[2][2] * v->z + m[2][3];
	return (res);
}

void		add_rows(double m[4][4], size_t i, size_t j, double mult)
{
	size_t		k;

	if (m && i != j)
	{
		k = 0;
		while (k < 4)
		{
			m[i][k] += m[j][k] * mult;
			k++;
		}
	}
	else
		ft_printf("add_rows error!\n");
}
