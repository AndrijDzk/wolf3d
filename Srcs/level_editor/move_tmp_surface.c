/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_tmp_surface.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 11:28:59 by adzikovs          #+#    #+#             */
/*   Updated: 2018/11/03 10:50:14 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "intersections.h"

#include "common.h"

#include "level_editor_typedefs.h"

void	bring_vertical_surfaces_together(t_game_data *data, char dir)
{
	if (dir >= 0)
	{
		data->new_surface->plane.pos.x = data->base_surface->plane.pos.x +
			data->base_surface->length * data->base_surface->plane.norm.z;
		data->new_surface->plane.pos.z = data->base_surface->plane.pos.z -
			data->base_surface->length * data->base_surface->plane.norm.x;
	}
	else
	{
		data->new_surface->plane.pos.x = data->base_surface->plane.pos.x;
		data->new_surface->plane.pos.z = data->base_surface->plane.pos.z;
	}
}

int		perform_rooted_tmp_surface_move(t_game_data *data, char dir)
{
	data->new_surface->plane.pos.x += dir * data->base_surface->plane.norm.z;
	data->new_surface->plane.pos.z -= dir * data->base_surface->plane.norm.x;
	if (rebuild_bsp_tree(data->scene))
		return (1);
	return (0);
}

int		move_rooted_tmp_surface(t_sdl *sdl, t_game_data *data, SDL_Event e)
{
	char dir;

	if (data == NULL || data->new_surface == NULL ||
		data->base_surface == NULL || data->exists == 0 ||
		fabs(data->base_surface->plane.norm.y) > DBL_ZERO ||
		fabs(data->new_surface->plane.norm.y) > DBL_ZERO ||
		surfaces_intersection(
		data->base_surface, data->new_surface, NULL) == 0)
		return (1);
	if (e.key.keysym.sym == SDLK_l)
		dir = 1;
	else if (e.key.keysym.sym == SDLK_j)
		dir = -1;
	else
		return (1);
	bring_vertical_surfaces_together(data, dir);
	if (rebuild_bsp_tree(data->scene))
		return (1);
	render_scene(sdl, data->scene, data->camera);
	throw_current_image_on_screen(sdl);
	return (0);
}

int		move_free_tmp_surface(t_sdl *sdl, t_game_data *data, SDL_Event e)
{
	if (data == NULL || data->new_surface == NULL || data->exists == 0)
		return (1);
	if (e.key.keysym.sym == SDLK_l)
		data->new_surface->plane.pos.x += 1;
	else if (e.key.keysym.sym == SDLK_j)
		data->new_surface->plane.pos.x -= 1;
	else if (e.key.keysym.sym == SDLK_i)
		data->new_surface->plane.pos.z -= 1;
	else if (e.key.keysym.sym == SDLK_k)
		data->new_surface->plane.pos.z += 1;
	else if (e.key.keysym.sym == SDLK_y && data->base_surface == NULL)
		data->new_surface->plane.pos.y += 1;
	else if (e.key.keysym.sym == SDLK_h && data->base_surface == NULL)
		data->new_surface->plane.pos.y -= 1;
	else
		return (1);
	if (rebuild_bsp_tree(data->scene))
		return (1);
	render_scene(sdl, data->scene, data->camera);
	throw_current_image_on_screen(sdl);
	return (0);
}

int		move_tmp_surface(t_sdl *sdl, t_game_data *data, SDL_Event e)
{
	if (sdl == NULL || data == NULL)
		return (1);
	else if (data->new_surface == NULL)
		return (0);
	else if (data->base_surface &&
		fabs(data->base_surface->plane.norm.y) <= DBL_ZERO &&
		fabs(data->new_surface->plane.norm.y) <= DBL_ZERO)
		return (move_rooted_tmp_surface(sdl, data, e));
	else
		return (move_free_tmp_surface(sdl, data, e));
}
