/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/12 15:21:37 by adzikovs          #+#    #+#             */
/*   Updated: 2018/10/12 15:27:35 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "common_typedefs.h"

t_vec3d			rotate_x(t_vec3d const *v, const double a)
{
	t_vec3d		res;

	res.x = v->x;
	res.y = v->y * cos(a) - v->z * sin(a);
	res.z = v->y * sin(a) + v->z * cos(a);
	return (res);
}

t_vec3d			rotate_y(t_vec3d const *v, const double a)
{
	t_vec3d		res;

	res.x = v->x * cos(a) + v->z * sin(a);
	res.y = v->y;
	res.z = -v->x * sin(a) + v->z * cos(a);
	return (res);
}

t_vec3d			rotate_z(t_vec3d const *v, const double a)
{
	t_vec3d		res;

	res.x = v->x * cos(a) - v->y * sin(a);
	res.y = v->x * sin(a) + v->y * cos(a);
	res.z = v->z;
	return (res);
}
