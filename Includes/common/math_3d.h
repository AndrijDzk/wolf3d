/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_3d.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 10:39:38 by adzikovs          #+#    #+#             */
/*   Updated: 2018/11/21 12:32:20 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATH_3D_H
# define MATH_3D_H

# include "common_typedefs.h"

char			check_limits(double l1, double l2, double val);

char			check_limits_inclusive(double l1, double l2, double val);

t_2d_segment	surface_into_2d_segment(const t_surface *s);

t_vec3d			t_vec2d_into_t_vec3d(t_vec2d v, double y);

int				point_pos_rel_to_quad(const t_2d_segment quad[4],
					const t_vec2d *p);

int				get_left_and_right_borders(
					t_textured_2d_segment *segments[5], char order,
					t_textured_2d_segment *left[5],
					t_textured_2d_segment *right[5]);

int				get_border_min_and_max_y(
					t_textured_2d_segment *segments[5],
					int *res_min,
					int *res_max);

int				build_line(const t_vec3d *v1, const t_vec3d *v2,
					t_2d_segment *res, t_2d_segment **res_ptr);

int				build_lines(t_vec3d *vertex[9],
					t_2d_segment res[8], t_2d_segment *res_ptr[8]);

#endif
