/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_crd_system.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/12 15:29:25 by adzikovs          #+#    #+#             */
/*   Updated: 2018/10/14 12:00:22 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include "t_vec3d_math.h"
#include "matrix_math.h"

void			get_rotated_basis(double *res,
					t_vec3d (*rot_fp)(t_vec3d const *, const double),
					double angle, size_t line_size)
{
	t_vec3d		tmp;

	tmp.x = 1;
	tmp.y = 0;
	tmp.z = 0;
	tmp = (*rot_fp)(&tmp, angle);
	t_vec3d_into_column(res, &tmp, line_size, 0);
	tmp.x = 0;
	tmp.y = 1;
	tmp.z = 0;
	tmp = (*rot_fp)(&tmp, angle);
	t_vec3d_into_column(res, &tmp, line_size, 1);
	tmp.x = 0;
	tmp.y = 0;
	tmp.z = 1;
	tmp = (*rot_fp)(&tmp, angle);
	t_vec3d_into_column(res, &tmp, line_size, 2);
}

void			rotate_crd_system(double m[4][4], double new_basis[4][4])
{
	t_vec3d		tmp;
	t_vec3d		crd;

	column_into_t_vec3d(*m, &crd, 4, 3);
	m[0][3] = 0;
	m[1][3] = 0;
	m[2][3] = 0;
	column_into_t_vec3d(&(new_basis[0][0]), &tmp, 4, 0);
	tmp = matrix_4x4_mult_t_vec3d(m, &tmp);
	t_vec3d_into_column(&(new_basis[0][0]), &tmp, 4, 0);
	column_into_t_vec3d(&(new_basis[0][0]), &tmp, 4, 1);
	tmp = matrix_4x4_mult_t_vec3d(m, &tmp);
	t_vec3d_into_column(&(new_basis[0][0]), &tmp, 4, 1);
	column_into_t_vec3d(&(new_basis[0][0]), &tmp, 4, 2);
	tmp = matrix_4x4_mult_t_vec3d(m, &tmp);
	t_vec3d_into_column(&(new_basis[0][0]), &tmp, 4, 2);
	ft_memcpy(m, new_basis, sizeof(double) * 16);
	t_vec3d_into_column(*m, &crd, 4, 3);
	ft_memset(m[3], 0, sizeof(double) * 3);
	m[3][3] = 1;
}

void			rotate_crd_system_around_x(double m[4][4], double angle)
{
	double		new_basis[4][4];

	get_rotated_basis(&(new_basis[0][0]), &rotate_x, angle, 4);
	rotate_crd_system(m, new_basis);
}

void			rotate_crd_system_around_y(double m[4][4], double angle)
{
	double		new_basis[4][4];

	get_rotated_basis(&(new_basis[0][0]), &rotate_y, angle, 4);
	rotate_crd_system(m, new_basis);
}

void			rotate_crd_system_around_z(double m[4][4], double angle)
{
	double		new_basis[4][4];

	get_rotated_basis(&(new_basis[0][0]), &rotate_z, angle, 4);
	rotate_crd_system(m, new_basis);
}
