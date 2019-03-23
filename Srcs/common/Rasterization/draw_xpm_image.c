/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_xpm_image.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 11:53:31 by adzikovs          #+#    #+#             */
/*   Updated: 2018/11/12 15:14:03 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"
/*
**static int			draw_xpm_image_error_exit(int fd)
**{
**	close(fd);
**	return (1);
**}
**
**int					draw_xpm_image(t_sdl *sdl, char *filename)
**{
**	int				fd;
**	int				x;
**	int				y;
**	char			*line;
**	t_xpm_header	header;
**	t_xpm_color		*colors;
**	SDL_Color		*color;
**
**	if (sdl == NULL || filename == NULL)
**		return (1);
**	clear_window(sdl);
**	if ((fd = open(filename, O_RDONLY)) < 0)
**		return (1);
**	if (read_xpm_header(fd, &header))
**		return (draw_xpm_image_error_exit(fd));
**	if ((colors = read_xpm_colors(fd, (size_t)header.colors)) == NULL)
**		return (draw_xpm_image_error_exit(fd));
**	y = 0;
**	while (get_next_line(fd, &line) > 0)
**	{
**		x = 0;
**		while (line[x])
**		{
**			color = find_xpm_color(colors, line[x], (size_t)header.colors);
**			if (color)
**			{
**				draw_point(sdl, color, x, y);
**				draw_point(sdl, color, x + 1, y);
**				draw_point(sdl, color, x + 2, y);
**				draw_point(sdl, color, x, y + 1);
**				draw_point(sdl, color, x + 1, y + 1);
**				draw_point(sdl, color, x + 2, y + 1);
**			}
**			x += 3;
**		}
**		free(line);
**		y += 2;
**	}
**	free(line);
**	free(colors);
**	close(fd);
**	return (0);
**}
*/
