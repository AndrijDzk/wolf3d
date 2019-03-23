/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_setting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/17 11:03:53 by adzikovs          #+#    #+#             */
/*   Updated: 2018/11/17 11:03:53 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "level_editor_defines.h"

#include "level_editor_typedefs.h"

static void		init_arrays(enum e_setting *codes, char **strings)
{
	codes[0] = esTextures;
	strings[0] = "Textures";
}

enum e_setting	is_setting(char *line)
{
	static enum e_setting	codes[LEVEL_EDITOR_SETTINGS_AM];
	static char				*strings[LEVEL_EDITOR_SETTINGS_AM];
	static char				flag_init = 0;
	size_t					i;

	if (!flag_init)
		init_arrays(codes, strings);
	i = 0;
	while (i < LEVEL_EDITOR_SETTINGS_AM)
	{
		if (ft_strcmp(line, strings[i]) == 0)
			return (codes[i]);
		i++;
	}
	return (esNot);
}
