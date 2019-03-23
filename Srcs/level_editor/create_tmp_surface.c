/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tmp_surface.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/22 14:32:05 by adzikovs          #+#    #+#             */
/*   Updated: 2018/11/23 12:24:18 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <common_typedefs.h>

#include "common.h"

#include "level_editor_typedefs.h"

int		create_new_rooted_surface(t_game_data *data)
{
	if (data == NULL || data->base_surface == NULL)
		return (1);
	if (fabs(data->base_surface->plane.norm.y) > DBL_ZERO)
		return (1);
	data->new_surface = (t_surface*)malloc(sizeof(*data->new_surface));
	data->new_surface->plane.norm.x = data->base_surface->plane.norm.z;
	data->new_surface->plane.norm.y = 0;
	data->new_surface->plane.norm.z = -data->base_surface->plane.norm.x;
	data->new_surface->plane.pos = data->base_surface->plane.pos;
	data->new_surface->length = data->base_surface->length;
	data->new_surface->height = data->base_surface->height;
	data->new_surface->inf = data->base_surface->inf;
	data->new_surface->visual_type = data->base_surface->visual_type;
	data->new_surface->visual = data->base_surface->visual;
	data->exists = 1;
	t_list_push_back(&data->scene->container.l_surfaces,
		data->new_surface, sizeof(*data->new_surface));
	if (rebuild_bsp_tree(data->scene))
		return (1);
	return (0);
}

int		create_new_free_surface(t_game_data *data)
{
	if (data == NULL)
		return (1);
	data->new_surface = (t_surface*)malloc(sizeof(*data->new_surface));
	data->new_surface->plane.norm.x = 0;
	data->new_surface->plane.norm.y = 0;
	data->new_surface->plane.norm.z = 1;
	ft_bzero(&data->new_surface->plane.pos, sizeof(t_vec3d));
	data->new_surface->length = 100;
	data->new_surface->height = 100;
	data->new_surface->inf = 0;
	data->new_surface->visual_type = evtTexture;
	data->new_surface->visual.texture = *data->textures[0];
	data->exists = 1;
	t_list_push_back(&data->scene->container.l_surfaces,
		data->new_surface, sizeof(*data->new_surface));
	if (rebuild_bsp_tree(data->scene))
		return (1);
	return (0);
}

int		create_new_surface(t_game_data *data)
{
	if (data == NULL)
		return (1);
	if (data->base_surface)
		return (create_new_rooted_surface(data));
	else
		return (create_new_free_surface(data));
}

int		create_or_destroy_tmp_surface(t_sdl *sdl,
			t_game_data *data, SDL_Event e)
{
	if (e.key.keysym.sym == SDLK_RETURN)
	{
		if (create_new_surface(data) == 0)
			ft_printf("Created tmp surface.\n");
		else
			return (1);
	}
	render_scene(sdl, data->scene, data->camera);
	throw_current_image_on_screen(sdl);
	return (0);
}
