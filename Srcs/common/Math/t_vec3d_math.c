/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_vec3d_math.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/12 12:15:05 by adzikovs          #+#    #+#             */
/*   Updated: 2018/10/19 12:07:43 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "common_typedefs.h"

t_vec3d			t_vec3d_add(t_vec3d const *v1, t_vec3d const *v2)
{
	t_vec3d		res;

	res.x = v1->x + v2->x;
	res.y = v1->y + v2->y;
	res.z = v1->z + v2->z;
	return (res);
}

t_vec3d			t_vec3d_sub(t_vec3d const *v1, t_vec3d const *v2)
{
	t_vec3d		res;

	res.x = v1->x - v2->x;
	res.y = v1->y - v2->y;
	res.z = v1->z - v2->z;
	return (res);
}

t_vec3d			t_vec3d_scal_mult(t_vec3d const *v, const double scal)
{
	t_vec3d		res;

	res.x = v->x * scal;
	res.y = v->y * scal;
	res.z = v->z * scal;
	return (res);
}

double			t_vec3d_dot_product(t_vec3d const *v1, t_vec3d const *v2)
{
	return (v1->x * v2->x + v1->y * v2->y + v1->z * v2->z);
}

t_vec3d			t_vec3d_cross_product(const t_vec3d *v1, const t_vec3d *v2)
{
	t_vec3d		res;

	res.x = v1->y * v2->z - v1->z * v2->y;
	res.y = v1->z * v2->x - v1->x * v2->z;
	res.z = v1->x * v2->y - v1->y * v2->x;
	return (res);
}
