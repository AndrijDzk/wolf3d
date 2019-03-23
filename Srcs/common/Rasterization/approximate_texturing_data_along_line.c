/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   approximate_texturing_data_along_line.c            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/10 09:50:49 by adzikovs          #+#    #+#             */
/*   Updated: 2018/11/10 10:50:26 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common_typedefs.h"

int		approximate_texturing_data_along_line(t_texturing_data *data)
{
	if (data == NULL || (data->bounds[1] - data->bounds[0]) == 0)
		return (1);
	data->x_z[1] = (data->x_z[1] - data->x_z[0]) /
		(data->bounds[1] - data->bounds[0]);
	data->y_z[1] = (data->y_z[1] - data->y_z[0]) /
		(data->bounds[1] - data->bounds[0]);
	data->one_z[1] = (data->one_z[1] - data->one_z[0]) /
		(data->bounds[1] - data->bounds[0]);
	return (0);
}
