/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 10:13:15 by adzikovs          #+#    #+#             */
/*   Updated: 2018/10/24 10:13:15 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H

# include "common_typedefs.h"

int		rotate_camera_around_x(t_sdl *sdl, t_scene *scene,
			t_camera *camera, enum e_input_action action);

int		rotate_camera_around_y(t_sdl *sdl, t_scene *scene,
			t_camera *camera, enum e_input_action action);

void	move_camera(t_camera *camera, t_vec3d const *dir, double speed);

int		move_camera_along_x(t_sdl *sdl, t_scene *scene,
			t_camera *camera, enum e_input_action action);

int		move_camera_along_y(t_sdl *sdl, t_scene *scene,
			t_camera *camera, enum e_input_action action);

int		move_camera_along_z(t_sdl *sdl, t_scene *scene,
			t_camera *camera, enum e_input_action action);

#endif
