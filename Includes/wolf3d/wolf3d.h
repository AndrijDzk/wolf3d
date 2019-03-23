/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/11 15:03:29 by adzikovs          #+#    #+#             */
/*   Updated: 2018/10/15 11:30:29 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# include "common_typedefs.h"

int		init(t_sdl *sdl);

int		main_loop(t_sdl *sdl, t_scene *scene, t_camera *camera);

#endif
