/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_base_surface.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 11:42:18 by adzikovs          #+#    #+#             */
/*   Updated: 2018/10/29 14:11:04 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "level_editor_typedefs.h"

#include "common.h"

#include "t_vec3d_math.h"

#include "matrix_math.h"

#include "intersections.h"

static t_ray	build_ray_to_cursor(t_sdl *sdl, t_camera *camera, SDL_Event e)
{
	t_ray		res;
	t_vec3d		pixel_crd;
	int			w;
	int			h;

	w = sdl->window.surface->w;
	h = sdl->window.surface->h;
	column_into_t_vec3d(&camera->m[0][0], &res.pos, 4, 3);
	if (SDL_GetRelativeMouseMode())
		pixel_crd = get_screen_pixel_crd(sdl, camera, w / 2, h / 2);
	else
		pixel_crd = get_screen_pixel_crd(sdl, camera, e.button.x, e.button.y);
	res.dir = get_dir(&res.pos, &pixel_crd);
	return (res);
}

int				select_base_surface(t_sdl *sdl, t_game_data *data, SDL_Event e)
{
	t_list		*tmp;
	t_ray		ray;
	double		min_dist;
	double		d;

	if (data == NULL || data->scene->cont_type != Cont_t_list)
		return (1);
	if (e.button.button != SDL_BUTTON_LEFT)
		return (0);
	data->base_surface = NULL;
	ray = build_ray_to_cursor(sdl, data->camera, e);
	min_dist = -1;
	tmp = data->scene->container.l_surfaces;
	while (tmp)
	{
		if ((d = ray_surface_intersection(&ray, tmp->data)) >= 0 &&
			(min_dist < 0 || d < min_dist))
		{
			min_dist = d;
			data->base_surface = tmp->data;
		}
		tmp = tmp->next;
	}
	return (0);
}
