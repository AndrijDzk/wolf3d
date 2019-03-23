/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   divide_surface.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/19 15:12:29 by adzikovs          #+#    #+#             */
/*   Updated: 2018/11/16 15:59:31 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_vec3d_math.h"

#include "bsp.h"

static int		vert_divide_fill_new_node_from_surface(
					t_surface *base_surface,
					t_bsp_node *new_node,
					t_vec3d const *diff,
					char flag_first)
{
	if (flag_first)
		new_node->surface->length = t_vec3d_mod(diff);
	else
	{
		new_node->surface->plane.pos =
			t_vec3d_add(&new_node->surface->plane.pos, diff);
		new_node->surface->length -= t_vec3d_mod(diff);
	}
	if (new_node->surface->visual_type == evtTexture)
		bsp_vert_divide_texture(base_surface, diff, new_node->surface,
			flag_first);
	new_node->initial_surface = base_surface;
	new_node->front = NULL;
	new_node->rear = NULL;
	return (0);
}

static int		bsp_vertically_divide_vertical_surface(
					t_surface *base_surface, const t_vec3d *div_pos,
					t_bsp_node *res1, t_bsp_node *res2)
{
	t_vec3d		diff;

	res1->surface = (t_surface*)malloc(sizeof(*(res1->surface)));
	res2->surface = (t_surface*)malloc(sizeof(*(res2->surface)));
	ft_memcpy(res1->surface, base_surface, sizeof(*base_surface));
	ft_memcpy(res2->surface, base_surface, sizeof(*base_surface));
	diff = t_vec3d_sub(div_pos, &base_surface->plane.pos);
	vert_divide_fill_new_node_from_surface(base_surface, res1, &diff, 1);
	vert_divide_fill_new_node_from_surface(base_surface, res2, &diff, 0);
	if (res1->rear || res1->front || res2->front || res2->rear)
	{
		ft_printf("bsp_divide_surface error!\n");
		return (1);
	}
	return (0);
}

static int		hor_divide_fill_new_node_from_surface(
					t_surface *base_surface,
					t_bsp_node *new_node,
					double vert_diff,
					char flag_first)
{
	if (flag_first)
		new_node->surface->height = vert_diff;
	else
	{
		new_node->surface->plane.pos.y += vert_diff;
		new_node->surface->height -= vert_diff;
	}
	if (new_node->surface->visual_type == evtTexture)
		bsp_hor_divide_texture(base_surface, vert_diff, new_node->surface,
			flag_first);
	new_node->initial_surface = base_surface;
	new_node->front = NULL;
	new_node->rear = NULL;
	return (0);
}

static int		bsp_horizontally_divide_vertical_surface(
					t_surface *base_surface, double intersection_y,
					t_bsp_node *res1, t_bsp_node *res2)
{
	double		vert_diff;

	vert_diff = intersection_y - base_surface->plane.pos.y;
	res1->surface = (t_surface*)malloc(sizeof(*(res1->surface)));
	res2->surface = (t_surface*)malloc(sizeof(*(res2->surface)));
	ft_memcpy(res1->surface, base_surface, sizeof(*base_surface));
	ft_memcpy(res2->surface, base_surface, sizeof(*base_surface));
	hor_divide_fill_new_node_from_surface(base_surface, res1, vert_diff, 1);
	hor_divide_fill_new_node_from_surface(base_surface, res2, vert_diff, 0);
	if (res1->rear || res1->front || res2->front || res2->rear)
	{
		ft_printf("bsp_divide_surface error!\n");
		return (1);
	}
	return (0);
}

int				bsp_divide_surface(
					t_surface *base_surface,
					const t_ray *div,
					t_bsp_node *res1, t_bsp_node *res2)
{
	if (base_surface == NULL || div == NULL ||
		res1 == NULL || res2 == NULL ||
		fabs(base_surface->plane.norm.y) > DBL_ZERO)
		return (1);
	else if (fabs(div->dir.y) > DBL_ZERO)
		return (bsp_vertically_divide_vertical_surface(
			base_surface, &div->pos, res1, res2));
	else
		return (bsp_horizontally_divide_vertical_surface(
			base_surface, div->pos.y, res1, res2));
}
