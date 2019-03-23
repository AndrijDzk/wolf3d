/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_vec3d_math.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/12 12:16:42 by adzikovs          #+#    #+#             */
/*   Updated: 2018/10/31 14:08:01 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_VEC3D_MATH_H
# define T_VEC3D_MATH_H

# include "common_typedefs.h"

t_vec3d		t_vec3d_add(t_vec3d const *v1, t_vec3d const *v2);

t_vec3d		t_vec3d_sub(t_vec3d const *v1, t_vec3d const *v2);

t_vec3d		t_vec3d_scal_mult(t_vec3d const *v, const double scal);

double		t_vec3d_dot_product(t_vec3d const *v1, t_vec3d const *v2);

t_vec3d		t_vec3d_cross_product(const t_vec3d *v1, const t_vec3d *v2);

double		t_vec3d_mod(const t_vec3d *v);

t_vec3d		rotate_x(t_vec3d const *v, const double a);

t_vec3d		rotate_y(t_vec3d const *v, const double a);

t_vec3d		rotate_z(t_vec3d const *v, const double a);

void		t_vec3d_norm(t_vec3d *v);

void		t_vec3d_into_column(double *arr, t_vec3d const *v,
				size_t line_size, size_t column);

void		column_into_t_vec3d(double const *arr, t_vec3d *v,
				size_t line_size, size_t column);

double		get_surface_point_rel_pos(const t_surface *surface,
				double x, double y, double z);

double		get_surface_surface_rel_pos(const t_surface *base_surface,
				const t_surface *test);

t_vec3d		get_dir(const t_vec3d *start, const t_vec3d *end);

#endif
