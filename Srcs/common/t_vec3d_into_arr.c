/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_vec3d_into_arr.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/14 11:57:54 by adzikovs          #+#    #+#             */
/*   Updated: 2018/10/15 14:26:55 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common_typedefs.h"

void			t_vec3d_into_column(double *arr, t_vec3d const *v,
				size_t line_size, size_t column)
{
	arr[column] = v->x;
	arr[column + line_size] = v->y;
	arr[column + 2 * line_size] = v->z;
}

void			column_into_t_vec3d(double const *arr, t_vec3d *v,
				size_t line_size, size_t column)
{
	v->x = arr[column];
	v->y = arr[column + line_size];
	v->z = arr[column + 2 * line_size];
}
