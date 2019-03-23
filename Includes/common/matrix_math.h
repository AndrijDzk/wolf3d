/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_math.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/12 12:38:07 by adzikovs          #+#    #+#             */
/*   Updated: 2018/11/07 12:51:35 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRIX_MATH_H
# define MATRIX_MATH_H

# include "common_typedefs.h"

t_vec3d		matrix_4x4_mult_t_vec3d(double m[4][4], t_vec3d const *v);

int			matrix_inverse(double m[4][4], double res[4][4]);

void		rotate_crd_system_around_world_x(double m[4][4], double angle);

void		rotate_crd_system_around_world_y(double m[4][4], double angle);

void		rotate_crd_system_around_world_z(double m[4][4], double angle);

void		rotate_crd_system_around_x(double m[4][4], double angle);

void		rotate_crd_system_around_y(double m[4][4], double angle);

void		rotate_crd_system_around_z(double m[4][4], double angle);

t_vec3d		get_screen_pixel_crd(t_sdl *sdl, t_camera *c, int x, int y);

void		add_rows(double m[4][4], size_t i, size_t j, double mult);

int			gj_eliminate_element(
				double copy[4][4],
				size_t i,
				size_t j,
				double res[4][4]);

int			correct_diagonal(double m[4][4], double res[4][4]);

#endif
