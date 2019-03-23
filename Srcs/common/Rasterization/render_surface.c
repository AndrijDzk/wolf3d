/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_surface.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/21 14:11:52 by adzikovs          #+#    #+#             */
/*   Updated: 2018/11/11 14:51:44 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rasterization.h"

#include "matrix_math.h"

#include "common.h"

/*
**static int		translate_vertexes_into_camera_crd(t_camera *camera,
**					t_vec3d vertexes[4])
**{
**	size_t		i;
**	double		m_inv[4][4];
**
**	if (camera_matrix_inverse(camera->m, m_inv))
**		return (1);
**	i = 0;
**	while (i < 4)
**	{
**		vertexes[i] = matrix_4x4_mult_t_vec3d(m_inv, vertexes + i);
**		i++;
**	}
**	return (0);
**}
**
**static char		get_surface_order(
**					const t_surface *surface,
**					const t_camera *camera)
**{
**	if (surface == NULL || camera == NULL)
**		return (0);
**	if (get_surface_point_rel_pos(
**			surface,
**			camera->m[0][3],
**			camera->m[1][3],
**			camera->m[2][3]) >= 0)
**		return (1);
**	else
**		return (0);
**}
**
**int				render_surface_rasterization(t_sdl *sdl, t_camera *camera,
**					t_surface *surface)
**{
**	t_vec3d		vertex[4];
**	t_vec3d		proj_data[8];
**	t_vec3d		*proj_pointers[9];
**	size_t		i;
**	char		order;
**
**	ft_bzero(proj_pointers, sizeof(*proj_pointers) * 9);
**	order = get_surface_order(surface, camera);
**	if (rasterization_get_vertex_crd(surface, vertex))
**		return (1);
**	if (translate_vertexes_into_camera_crd(camera, vertex))
**		return (1);
**	if (rasterization_get_vertex_projections(vertex, proj_data, proj_pointers))
**		return (1);
**	i = 0;
**	while (i < 9 && proj_pointers[i])
**	{
**		proj_pointers[i]->x += (double)sdl->window.surface->w / 2;
**		proj_pointers[i]->y *= -1;
**		proj_pointers[i]->y += (double)sdl->window.surface->h / 2;
**		i++;
**	}
**	if (draw_polygon(sdl, proj_pointers, &surface->visual.color, order))
**		return (1);
**	return (0);
**}
*/
