/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer_slave.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 14:20:26 by adzikovs          #+#    #+#             */
/*   Updated: 2018/11/07 14:36:57 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix_math.h"

#include "common.h"

SDL_Color				generate_ray(
							t_scene *scene,
							t_vec3d *pixel_world,
							t_camera *camera)
{
	t_ray	ray;

	ray.pos.x = camera->m[0][3];
	ray.pos.y = camera->m[1][3];
	ray.pos.z = camera->m[2][3];
	ray.dir = t_vec3d_sub(pixel_world, &(ray.pos));
	t_vec3d_norm(&(ray.dir));
	return (get_ray_color(scene, &ray));
}

static void				init_pixel_camera(
							t_renderer_slave_param *param,
							t_vec3d *pixel_camera)
{
	pixel_camera->z = param->camera->focal_length;
	pixel_camera->y = param->camera->y_scale *
		((double)param->sdl->window.surface->h / 2 - param->y_start);
}

static inline void		move_pixel_along_camera_x(
							t_vec3d *pixel,
							const t_camera *camera)
{
	pixel->x += camera->x_scale * camera->m[0][0];
	pixel->y += camera->x_scale * camera->m[1][0];
	pixel->z += camera->x_scale * camera->m[2][0];
}

void					*raycasting_renderer_slave_body(
							t_renderer_slave_param *param)
{
	t_vec3d		pixel_camera;
	t_vec3d		pixel_world;
	SDL_Color	color;
	int			x;
	int			y;

	init_pixel_camera(param, &pixel_camera);
	y = param->y_start;
	while (y < param->y_end)
	{
		pixel_camera.x = param->camera->x_scale *
			(param->x_start - (double)param->sdl->window.surface->w / 2);
		pixel_world = matrix_4x4_mult_t_vec3d(param->camera->m, &pixel_camera);
		x = param->x_start;
		while (x < param->x_end)
		{
			color = generate_ray(param->scene, &pixel_world, param->camera);
			draw_point(param->sdl, &color, x, y);
			move_pixel_along_camera_x(&pixel_world, param->camera);
			x++;
		}
		pixel_camera.y -= param->camera->y_scale;
		y++;
	}
	return (NULL);
}

void					*raycast_renderer_slave(void *param)
{
	return (raycasting_renderer_slave_body(param));
}
