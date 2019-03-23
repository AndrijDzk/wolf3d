/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_tmp_surface.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/03 10:39:05 by adzikovs          #+#    #+#             */
/*   Updated: 2018/11/17 14:26:34 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <common_typedefs.h>
#include "level_editor.h"

#include "common.h"

#define COLOR_SPEED 10
#define SIZE_SPEED 10

#define EVENT_KEY(event) event.key.keysym.sym

static int		change_color(t_sdl *sdl, t_game_data *data, SDL_Event e)
{
	SDL_Color	*color;

	color = &data->new_surface->visual.color;
	if (e.key.keysym.sym == SDLK_KP_7 && color->r >= COLOR_SPEED)
		color->r -= COLOR_SPEED;
	else if (e.key.keysym.sym == SDLK_KP_8 && color->r <= (255 - COLOR_SPEED))
		color->r += COLOR_SPEED;
	else if (e.key.keysym.sym == SDLK_KP_4 && color->g >= COLOR_SPEED)
		color->g -= COLOR_SPEED;
	else if (e.key.keysym.sym == SDLK_KP_5 && color->g <= (255 - COLOR_SPEED))
		color->g += COLOR_SPEED;
	else if (e.key.keysym.sym == SDLK_KP_1 && color->b >= COLOR_SPEED)
		color->b -= COLOR_SPEED;
	else if (e.key.keysym.sym == SDLK_KP_2 && color->b <= (255 - COLOR_SPEED))
		color->b += COLOR_SPEED;
	if (rebuild_bsp_tree(data->scene))
		return (1);
	render_scene(sdl, data->scene, data->camera);
	throw_current_image_on_screen(sdl);
	return (0);
}

static int		change_texture(t_sdl *sdl, t_game_data *data, SDL_Event e)
{
	size_t		i;
	size_t		j;

	i = 0;
	while (data->textures[i])
	{
		if (data->textures[i]->data == data->new_surface->visual.texture.data)
			break ;
		i++;
	}
	if (data->textures[i] == NULL)
		return (0);
	if (data->textures[i + 1] && EVENT_KEY(e) == SDLK_KP_8)
		j = i + 1;
	else if (i > 0 && EVENT_KEY(e) == SDLK_KP_7)
		j = i - 1;
	else
		j = 0;
	calculate_new_texture_data(data->textures[i], data->textures[j],
		&data->new_surface->visual.texture);
	if (rebuild_bsp_tree(data->scene))
		return (1);
	render_scene(sdl, data->scene, data->camera);
	throw_current_image_on_screen(sdl);
	return (0);
}

static int		change_visual(t_sdl *sdl, t_game_data *data, SDL_Event e)
{
	if (data->new_surface->visual_type == evtColor)
		return (change_color(sdl, data, e));
	else if (data->new_surface->visual_type == evtTexture)
		return (change_texture(sdl, data, e));
	else
	{
		ft_printf("change_visual: unknown visual type!\n");
		return (0);
	}
}

static int		change_size(t_sdl *sdl, t_game_data *data, SDL_Event e)
{
	if (e.key.keysym.sym == SDLK_v && data->new_surface->length > SIZE_SPEED)
		data->new_surface->length -= SIZE_SPEED;
	else if (e.key.keysym.sym == SDLK_b)
		data->new_surface->length += SIZE_SPEED;
	else if (e.key.keysym.sym == SDLK_n &&
				data->new_surface->height > SIZE_SPEED)
		data->new_surface->height -= SIZE_SPEED;
	else if (e.key.keysym.sym == SDLK_m)
		data->new_surface->height += SIZE_SPEED;
	if (rebuild_bsp_tree(data->scene))
		return (1);
	render_scene(sdl, data->scene, data->camera);
	throw_current_image_on_screen(sdl);
	return (0);
}

int				change_tmp_surface(t_sdl *sdl, t_game_data *data, SDL_Event e)
{
	if (sdl == NULL || data == NULL)
		return (1);
	if (data->new_surface)
	{
		if (e.key.keysym.sym == SDLK_KP_7 || e.key.keysym.sym == SDLK_KP_8 ||
			e.key.keysym.sym == SDLK_KP_4 || e.key.keysym.sym == SDLK_KP_5 ||
			e.key.keysym.sym == SDLK_KP_1 || e.key.keysym.sym == SDLK_KP_2)
			return (change_visual(sdl, data, e));
		else if (e.key.keysym.sym == SDLK_v || e.key.keysym.sym == SDLK_b ||
					e.key.keysym.sym == SDLK_n || e.key.keysym.sym == SDLK_m)
			return (change_size(sdl, data, e));
	}
	return (0);
}
