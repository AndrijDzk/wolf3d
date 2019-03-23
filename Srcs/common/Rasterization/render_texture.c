/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_texture.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/21 14:11:52 by adzikovs          #+#    #+#             */
/*   Updated: 2018/11/24 10:51:27 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <common_typedefs.h>
#include "matrix_math.h"

#include "rasterization.h"

#include "common.h"

static int		translate_vertexes_into_camera_crd(t_camera *camera,
					t_vec3d vertexes[4])
{
	size_t		i;
	double		m_inv[4][4];

	if (camera_matrix_inverse(camera->m, m_inv))
		return (1);
	i = 0;
	while (i < 4)
	{
		vertexes[i] = matrix_4x4_mult_t_vec3d(m_inv, vertexes + i);
		i++;
	}
	return (0);
}

static char		get_surface_order(
					const t_surface *surface,
					const t_camera *camera)
{
	if (surface == NULL || camera == NULL)
		return (0);
	if (get_surface_point_rel_pos(
			surface,
			camera->m[0][3],
			camera->m[1][3],
			camera->m[2][3]) >= 0)
		return (1);
	else
		return (0);
}

static void		init_arrays(
					t_textured_2d_segment proj_data[5],
					t_textured_2d_segment *proj_ptrs[5])
{
	size_t		i;

	ft_bzero(proj_data, sizeof(*proj_data) * 5);
	i = 0;
	while (i < 5)
	{
		proj_ptrs[i] = proj_data + i;
		i++;
	}
}

int				render_texture_rasterization(t_sdl *sdl, t_camera *camera,
					t_surface *surface)
{
	t_vec3d					vertex[4];
	t_textured_2d_segment	proj_data[5];
	t_textured_2d_segment	*proj_ptrs[5];
	char					order;

	if (surface->visual_type != evtTexture)
		return (1);
	init_arrays(proj_data, proj_ptrs);
	order = get_surface_order(surface, camera);
	if (rasterization_get_vertex_crd(surface, vertex))
		return (1);
	if (translate_vertexes_into_camera_crd(camera, vertex))
		return (1);
	get_texture_projection(camera, vertex, proj_ptrs);
	draw_texture_multithreaded(order, sdl, proj_ptrs, &surface->visual.texture);
	return (0);
}
