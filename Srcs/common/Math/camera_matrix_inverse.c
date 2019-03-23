/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_matrix_inverse.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/11 14:35:24 by adzikovs          #+#    #+#             */
/*   Updated: 2018/11/11 14:35:24 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_vec3d_math.h"

#include "matrix_math.h"

int				get_new_crd(double m[4][4], double m_inv[4][4])
{
	m_inv[0][3] = -m[0][3] * m_inv[0][0] - m[1][3] * m_inv[0][1] -
		m[2][3] * m_inv[0][2];
	m_inv[1][3] = -m[0][3] * m_inv[1][0] - m[1][3] * m_inv[1][1] -
		m[2][3] * m_inv[1][2];
	m_inv[2][3] = -m[0][3] * m_inv[2][0] - m[1][3] * m_inv[2][1] -
		m[2][3] * m_inv[2][2];
	return (0);
}

int				camera_matrix_inverse(double m[4][4], double m_inv[4][4])
{
	t_vec3d		tmp;

	if (matrix_inverse(m, m_inv))
		return (1);
	column_into_t_vec3d(&m_inv[0][0], &tmp, 4, 0);
	t_vec3d_norm(&tmp);
	t_vec3d_into_column(&m_inv[0][0], &tmp, 4, 0);
	column_into_t_vec3d(&m_inv[0][0], &tmp, 4, 1);
	t_vec3d_norm(&tmp);
	t_vec3d_into_column(&m_inv[0][0], &tmp, 4, 1);
	column_into_t_vec3d(&m_inv[0][0], &tmp, 4, 2);
	t_vec3d_norm(&tmp);
	t_vec3d_into_column(&m_inv[0][0], &tmp, 4, 2);
	get_new_crd(m, m_inv);
	return (0);
}
