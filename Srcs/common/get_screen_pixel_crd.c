/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_screen_pixel_crd.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 11:51:52 by adzikovs          #+#    #+#             */
/*   Updated: 2018/10/29 11:52:24 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common_typedefs.h"

t_vec3d		get_screen_pixel_crd(t_sdl *sdl, t_camera *c, int x, int y)
{
	t_vec3d		res;
	double		x_crd;
	double		y_crd;
	double		z_crd;

	x_crd = -(double)sdl->window.surface->w / 2 + ((double)x + 0.5);
	y_crd = (double)sdl->window.surface->h / 2 - ((double)y + 0.5);
	z_crd = c->focal_length;
	res.x = c->m[0][3];
	res.x += x_crd * c->m[0][0] + y_crd * c->m[0][1] + z_crd * c->m[0][2];
	res.y = c->m[1][3];
	res.y += x_crd * c->m[1][0] + y_crd * c->m[1][1] + z_crd * c->m[1][2];
	res.z = c->m[2][3];
	res.z += x_crd * c->m[2][0] + y_crd * c->m[2][1] + z_crd * c->m[2][2];
	return (res);
}
