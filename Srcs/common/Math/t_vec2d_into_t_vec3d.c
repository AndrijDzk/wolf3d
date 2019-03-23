/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_vec2d_into_t_vec3d.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 12:26:56 by adzikovs          #+#    #+#             */
/*   Updated: 2018/11/21 12:26:56 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common_typedefs.h"

t_vec3d			t_vec2d_into_t_vec3d(t_vec2d v, double y)
{
	t_vec3d		res;

	res.x = v.x;
	res.y = y;
	res.z = v.y;
	return (res);
}
