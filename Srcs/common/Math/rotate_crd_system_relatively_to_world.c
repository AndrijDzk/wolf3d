/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_crd_system_relatively_to_world.c            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/14 11:55:42 by adzikovs          #+#    #+#             */
/*   Updated: 2018/10/14 13:08:06 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_vec3d_math.h"

void			rotate_column(double *start, double angle,
					t_vec3d (*rot_fp)(t_vec3d const *, const double))
{
	t_vec3d		tmp;

	tmp.x = start[0];
	tmp.y = start[4];
	tmp.z = start[8];
	tmp = (*rot_fp)(&tmp, angle);
	t_vec3d_norm(&tmp);
	start[0] = tmp.x;
	start[4] = tmp.y;
	start[8] = tmp.z;
}

void			rotate_crd_system_around_world_x(double m[4][4], double angle)
{
	rotate_column(&(m[0][0]), angle, &rotate_x);
	rotate_column(&(m[0][1]), angle, &rotate_x);
	rotate_column(&(m[0][2]), angle, &rotate_x);
}

void			rotate_crd_system_around_world_y(double m[4][4], double angle)
{
	rotate_column(&(m[0][0]), angle, &rotate_y);
	rotate_column(&(m[0][1]), angle, &rotate_y);
	rotate_column(&(m[0][2]), angle, &rotate_y);
}

void			rotate_crd_system_around_world_z(double m[4][4], double angle)
{
	rotate_column(&(m[0][0]), angle, &rotate_z);
	rotate_column(&(m[0][1]), angle, &rotate_z);
	rotate_column(&(m[0][2]), angle, &rotate_z);
}
