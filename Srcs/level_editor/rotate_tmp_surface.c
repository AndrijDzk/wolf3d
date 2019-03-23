/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_tmp_surface.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/28 11:23:17 by adzikovs          #+#    #+#             */
/*   Updated: 2018/11/08 10:01:18 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_vec3d_math.h"

#include "level_editor_typedefs.h"

#include "common.h"

static char		correct_norm(t_vec3d *norm, double *to_check)
{
	double		tmp;

	tmp = 0;
	if (fabs(*to_check - 1) <= 0.0002)
		tmp = 1;
	else if (fabs(*to_check + 1) <= 0.0002)
		tmp = -1;
	if (fabs(tmp) > DBL_ZERO)
	{
		ft_bzero(norm, sizeof(*norm));
		*to_check = tmp;
		return (1);
	}
	return (0);
}

static void		change_plane_orientation(t_vec3d *norm)
{
	if (fabs(norm->y) > DBL_ZERO)
	{
		norm->x = 0;
		norm->y = 0;
		norm->z = 1;
	}
	else
	{
		norm->x = 0;
		norm->y = 1;
		norm->z = 0;
	}
}

static int		perform_rotate(SDL_Event e, t_vec3d *norm)
{
	if (e.key.keysym.sym == SDLK_u)
		*norm = rotate_y(norm, 0.03);
	else if (e.key.keysym.sym == SDLK_o)
		*norm = rotate_y(norm, -0.03);
	else if (e.key.keysym.sym == SDLK_p)
		change_plane_orientation(norm);
	if (e.key.keysym.sym == SDLK_u ||
		e.key.keysym.sym == SDLK_o)
	{
		if (correct_norm(norm, &norm->x))
			return (0);
		else if (correct_norm(norm, &norm->z))
			return (0);
	}
	return (0);
}

int				rotate_tmp_surface(t_sdl *sdl, t_game_data *data, SDL_Event e)
{
	if (e.type != SDL_KEYDOWN || sdl == NULL || data == NULL)
		return (1);
	if (data->new_surface == NULL)
		return (0);
	perform_rotate(e, &data->new_surface->plane.norm);
	if (e.key.keysym.sym == SDLK_u ||
		e.key.keysym.sym == SDLK_o ||
		e.key.keysym.sym == SDLK_p)
	{
		if (rebuild_bsp_tree(data->scene))
			return (1);
		render_scene(sdl, data->scene, data->camera);
		throw_current_image_on_screen(sdl);
	}
	return (0);
}
