/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recalculate_texture_part.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/17 13:44:40 by adzikovs          #+#    #+#             */
/*   Updated: 2018/11/24 12:29:28 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common_typedefs.h"

int		calculate_new_texture_data(
			const t_xpm_texture *old_base,
			const t_xpm_texture *new_base,
			t_xpm_texture *texture_part)
{
	double	w_coeff;
	double	h_coeff;

	if (old_base == NULL || new_base == NULL || texture_part == NULL)
		return (1);
	w_coeff = new_base->header.w / (double)old_base->header.w;
	h_coeff = new_base->header.h / (double)old_base->header.h;
	texture_part->header.w = new_base->header.w;
	texture_part->header.h = new_base->header.h;
	texture_part->header.colors = new_base->header.colors;
	texture_part->header.chars_per_pixel = new_base->header.chars_per_pixel;
	texture_part->colors = new_base->colors;
	texture_part->x[0] = texture_part->x[0] * w_coeff;
	texture_part->x[1] = texture_part->x[1] * w_coeff;
	texture_part->y[0] = texture_part->y[0] * h_coeff;
	texture_part->y[1] = texture_part->y[1] * h_coeff;
	texture_part->data = new_base->data;
	return (0);
}
