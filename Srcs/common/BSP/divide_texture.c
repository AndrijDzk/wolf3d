/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   divide_texture.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 10:28:25 by adzikovs          #+#    #+#             */
/*   Updated: 2018/11/21 10:48:25 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <common_typedefs.h>
#include "t_vec3d_math.h"

static void	perform_hor_divide(
				const t_xpm_texture *old_texture,
				double coeff,
				t_xpm_texture *new_texture,
				char flag_first)
{
	ft_memcpy(&new_texture->header, &old_texture->header,
		sizeof(new_texture->header));
	new_texture->colors = old_texture->colors;
	ft_memcpy(new_texture->x, old_texture->x, sizeof(*new_texture->x) * 2);
	if (flag_first)
	{
		new_texture->y[0] = old_texture->y[0];
		new_texture->y[1] = coeff * old_texture->y[1];
	}
	else
	{
		new_texture->y[0] = old_texture->y[0] + coeff * old_texture->y[1];
		new_texture->y[1] = (1 - coeff) * old_texture->y[1];
	}
	new_texture->data = old_texture->data;
}

int			bsp_hor_divide_texture(
				const t_surface *base_surface,
				double vert_diff,
				t_surface *new_surface,
				char flag_first)
{
	double				coeff;

	if (base_surface == NULL || new_surface == NULL ||
		fabs(vert_diff) >= fabs(base_surface->height))
	{
		ft_printf("%$bsp_hor_divide_texture_error!\n", 2);
		exit(1);
	}
	if (new_surface->visual_type != evtTexture)
	{
		ft_printf("%$bsp_hor_divide_texture_error!\n", 2);
		exit(1);
	}
	coeff = vert_diff / base_surface->height;
	if (coeff < 0 || coeff >= 1)
	{
		ft_printf("%$bsp_hor_divide_texture_error!\n", 2);
		exit(1);
	}
	perform_hor_divide(&base_surface->visual.texture, coeff,
		&new_surface->visual.texture, flag_first);
	return (0);
}

static void	perfom_vert_divide(
				const t_xpm_texture *old_texture,
				double coeff,
				t_xpm_texture *new_texture,
				char flag_first)
{
	ft_memcpy(&new_texture->header, &old_texture->header,
		sizeof(new_texture->header));
	new_texture->colors = old_texture->colors;
	if (flag_first)
	{
		new_texture->x[0] = old_texture->x[0];
		new_texture->x[1] = coeff * old_texture->x[1];
	}
	else
	{
		new_texture->x[0] = old_texture->x[0] + coeff * old_texture->x[1];
		new_texture->x[1] = (1 - coeff) * old_texture->x[1];
	}
	ft_memcpy(new_texture->y, old_texture->y, sizeof(*new_texture->y) * 2);
	new_texture->data = old_texture->data;
}

int			bsp_vert_divide_texture(
				const t_surface *base_surface,
				const t_vec3d *diff,
				t_surface *new_surface,
				char flag_first)
{
	double				coeff;

	if (base_surface == NULL || new_surface == NULL ||
		diff == NULL)
	{
		ft_printf("%$bsp_vert_divide_texture_error!\n", 2);
		exit(1);
	}
	if (new_surface->visual_type != evtTexture)
	{
		ft_printf("%$bsp_vert_divide_texture_error!\n", 2);
		exit(1);
	}
	coeff = t_vec3d_mod(diff) / base_surface->length;
	if (coeff < 0 || coeff >= 1)
	{
		ft_printf("%$bsp_vert_divide_texture_error!\n", 2);
		exit(1);
	}
	perfom_vert_divide(&base_surface->visual.texture, coeff,
		&new_surface->visual.texture, flag_first);
	return (0);
}
