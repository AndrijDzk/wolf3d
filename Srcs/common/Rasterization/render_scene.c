/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_scene.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/21 11:57:45 by adzikovs          #+#    #+#             */
/*   Updated: 2018/11/03 09:49:34 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_vec3d_math.h"

#include "common.h"

#include "rasterization.h"

static void		traverse_node(t_bsp_node *node, t_list **stack,
					const t_vec3d *camera_pos)
{
	if (get_surface_point_rel_pos(node->surface, camera_pos->x,
			camera_pos->y, camera_pos->z) >= 0)
	{
		if (node->rear)
			t_list_push_front(stack, node->rear, sizeof(*node->rear));
		if (node->surface)
			t_list_push_front(stack, node->surface, sizeof(*node->surface));
		if (node->front)
			t_list_push_front(stack, node->front, sizeof(*node->front));
	}
	else
	{
		if (node->front)
			t_list_push_front(stack, node->front, sizeof(*node->front));
		if (node->surface)
			t_list_push_front(stack, node->surface, sizeof(*node->surface));
		if (node->rear)
			t_list_push_front(stack, node->rear, sizeof(*node->rear));
	}
}

void			clear_window(t_sdl *sdl)
{
	int			w;
	int			h;
	int			bpp;
	int			line_size;
	int			size;

	if (sdl)
	{
		w = sdl->window.surface->w;
		h = sdl->window.surface->h;
		bpp = sdl->window.surface->format->BytesPerPixel;
		line_size = w * bpp;
		size = h * line_size;
		if (size > 0)
			ft_bzero(sdl->window.surface->pixels, (size_t)size);
	}
}

void			*renderer_scene_rasterization(t_sdl *sdl, t_scene *scene,
					t_camera *camera)
{
	t_list		*stack;
	t_list		*tmp;
	t_vec3d		camera_pos;

	camera_pos.x = camera->m[0][3];
	camera_pos.y = camera->m[1][3];
	camera_pos.z = camera->m[2][3];
	clear_window(sdl);
	stack = NULL;
	if (scene->bsp_tree)
		t_list_push_front(&stack, scene->bsp_tree, sizeof(*scene->bsp_tree));
	while (stack)
	{
		tmp = stack;
		stack = stack->next;
		if (tmp->size == sizeof(t_bsp_node))
			traverse_node((t_bsp_node*)tmp->data, &stack, &camera_pos);
		else if (tmp->size == sizeof(t_surface))
			render_texture_rasterization(sdl, camera, (t_surface*)tmp->data);
		else
			ft_printf("render_scene_rasterization: unknow data in stack!\n");
		free(tmp);
	}
	draw_crosshair(sdl);
	return (NULL);
}
