/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_vec3d_operations.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 11:54:05 by adzikovs          #+#    #+#             */
/*   Updated: 2018/11/07 11:54:38 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_vec3d_math.h"

double			t_vec3d_mod(const t_vec3d *v)
{
	return (sqrt(v->x * v->x + v->y * v->y + v->z * v->z));
}

void			t_vec3d_norm(t_vec3d *v)
{
	double		len;

	len = v->x * v->x + v->y * v->y + v->z * v->z;
	len = sqrt(len);
	v->x = v->x / len;
	v->y = v->y / len;
	v->z = v->z / len;
}

t_vec3d			get_dir(const t_vec3d *start, const t_vec3d *end)
{
	t_vec3d		res;

	res = t_vec3d_sub(end, start);
	t_vec3d_norm(&res);
	return (res);
}
