/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_point_from_texture.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 10:18:51 by adzikovs          #+#    #+#             */
/*   Updated: 2018/11/21 13:52:37 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "common.h"

SDL_Color		*find_xpm_color(t_xpm_color *colors, char smb, size_t am)
{
	size_t			i;

	if (colors == NULL)
		return (NULL);
	i = 0;
	while (i < am)
	{
		if (smb == colors[i].smb)
			return (&colors[i].color);
		i++;
	}
	return (NULL);
}

SDL_Color		*get_point_from_xpm_texture(double x, double y,
					t_xpm_texture *txt)
{
	size_t		offset;
	int			x_r;
	int			y_r;

	if (x < 0)
		x = 0;
	else if (x > 1)
		x = 1;
	if (y < 0)
		y = 0;
	else if (y > 1)
		y = 1;
	x_r = (int)round(txt->x[0] + x * txt->x[1]);
	y_r = (int)round(txt->y[0] + y * txt->y[1]);
	offset = (size_t)y_r * txt->header.w + x_r;
	return (find_xpm_color(txt->colors, txt->data[offset], txt->header.colors));
}
