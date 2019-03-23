/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perspective_divide.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/11 13:58:25 by adzikovs          #+#    #+#             */
/*   Updated: 2018/11/24 10:30:44 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common_typedefs.h"

void	perspective_divide(t_vec3d *point, const int *focal_length)
{
	point->x /= point->z / *focal_length;
	point->y /= point->z / *focal_length;
}
