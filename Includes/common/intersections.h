/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 12:52:07 by adzikovs          #+#    #+#             */
/*   Updated: 2018/11/21 12:59:12 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERSECTIONS_H
# define INTERSECTIONS_H

# include "common_typedefs.h"

int			horizontal_and_vertical_surfaces_intersection(
				const t_surface *s1, const t_surface *s2, t_vec3d *res);

int			surfaces_intersection(
				const t_surface *s1, const t_surface *s2, t_vec3d *res);

int			line_plane_intersection(const t_ray *line,
				const t_plane *plane,
				t_vec3d *res);

int			ray_plane_intersection(const t_ray *ray,
					const t_plane *plane,
					t_vec3d *res);

double		ray_surface_intersection(t_ray const *ray,
				t_surface const *surface);

int			lines_2d_intersection(
				const t_2d_segment *s1,
				const t_2d_segment *s2,
				t_vec2d *res);

int			line_segment_2d_intersection(
				const t_2d_segment *line,
				const t_2d_segment *seg,
				t_vec2d *res);

int			segments_2d_intersection(
				const t_2d_segment *s1,
				const t_2d_segment *s2,
				t_vec2d *res);

int			segment_inside_quad(
				const t_2d_segment quad[4],
				const t_2d_segment *s,
				t_vec2d *res);

int			segment_lies_on_quad_edge(
				const t_2d_segment quad[4],
				const t_2d_segment *s,
				t_vec2d *res);

int			segment_quad_intersection(
				const t_2d_segment quad[4],
				const t_2d_segment *s,
				t_vec2d *res);

#endif
