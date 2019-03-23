/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_xpm_header.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 15:12:16 by adzikovs          #+#    #+#             */
/*   Updated: 2018/11/12 15:14:03 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common_typedefs.h"

static int	read_xpm_header_error_exit(char *line, char **words)
{
	if (line)
		free(line);
	if (words)
		free_2darr((void**)words);
	return (1);
}

int			read_xpm_header(int fd, t_xpm_header *res)
{
	char			*line;
	char			**words;

	if (res == NULL || fd < 0)
		return (1);
	if (get_next_line(fd, &line) <= 0)
		return (read_xpm_header_error_exit(line, NULL));
	words = ft_strsplit(line, " ");
	free(line);
	if (words[0] == NULL || words[1] == NULL ||
		words[2] == NULL || words[3] == NULL || words[4])
		return (read_xpm_header_error_exit(NULL, words));
	res->w = ft_atoi(words[0]);
	res->h = ft_atoi(words[1]);
	if (ft_atoi(words[2]) > 0)
		res->colors = (size_t)ft_atoi(words[2]);
	else
		return (read_xpm_header_error_exit(NULL, words));
	res->chars_per_pixel = ft_atoi(words[3]);
	free_2darr((void**)words);
	if (res->w <= 0 || res->h <= 0 || res->chars_per_pixel != 1)
		return (1);
	return (0);
}
