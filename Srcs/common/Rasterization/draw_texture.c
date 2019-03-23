/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 10:16:09 by adzikovs          #+#    #+#             */
/*   Updated: 2018/11/20 10:01:05 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rasterization.h"

int			draw_texture(
				t_sdl *sdl,
				t_xpm_texture *txt,
				t_texturing_table *table)
{
	int		y;
	size_t	i;

	if (txt == NULL || table == NULL)
		return (1);
	i = 0;
	y = table->y_start;
	while (y < table->y_end)
	{
		draw_texture_line(sdl, txt, y, table->rows + i);
		i++;
		y++;
	}
	return (0);
}
