/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_xpm_colors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 15:14:20 by adzikovs          #+#    #+#             */
/*   Updated: 2018/11/12 15:14:20 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common_typedefs.h"

int				read_xpm_color(char *text, SDL_Color *res)
{
	size_t		i;

	if (text == NULL || res == NULL || ft_strlen(text) != 7 || text[0] != '#')
		return (1);
	i = 1;
	while (text[i])
	{
		if (!ft_isdigit(text[i]) &&
			(ft_tolower(text[i]) < 'a' || 'z' < ft_tolower(text[i])))
			return (1);
		i++;
	}
	res->r = (uint8_t)ft_atoin_base(text + 1, 16, 2);
	res->g = (uint8_t)ft_atoin_base(text + 3, 16, 2);
	res->b = (uint8_t)ft_atoin_base(text + 5, 16, 2);
	return (0);
}

static void		*read_xpm_colors_error_exit(char *line, t_xpm_color *res)
{
	free(line);
	free(res);
	return (NULL);
}

t_xpm_color		*read_xpm_colors(int fd, size_t am)
{
	t_xpm_color	*res;
	size_t		i;
	char		*line;
	int			ret;

	if (fd < 0 || am == 0)
		return (NULL);
	res = (t_xpm_color*)malloc(sizeof(*res) * am);
	i = 0;
	while (i < am && (ret = get_next_line(fd, &line)) > 0)
	{
		if (ft_strlen(line) != 11)
			return (read_xpm_colors_error_exit(line, res));
		res[i].smb = line[0];
		if (read_xpm_color(line + 4, &res[i].color))
			return (read_xpm_colors_error_exit(line, res));
		free(line);
		i++;
	}
	if (ret < 0)
		free(line);
	return (res);
}
