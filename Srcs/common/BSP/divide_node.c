/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   divide_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 10:12:13 by adzikovs          #+#    #+#             */
/*   Updated: 2018/11/16 15:59:40 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_vec3d_math.h"

#include "bsp.h"

static int		vertical_divide_fill_new_node_from_old_node(
					t_bsp_node *base_node,
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
		bsp_vert_divide_texture(base_node->surface, diff, new_node->surface,
			flag_first);
	if (base_node->initial_surface)
		new_node->initial_surface = base_node->initial_surface;
	else
		new_node->initial_surface = base_node->surface;
	new_node->front = NULL;
	new_node->rear = NULL;
	return (0);
}

static int		bsp_vertically_divide_vertical_node(
					t_bsp_node **base_node, const t_vec3d *div_pos,
					t_bsp_node *res1, t_bsp_node *res2)
{
	t_vec3d		diff;
	t_bsp_node	*base_tmp;

	base_tmp = *base_node;
	res1->surface = (t_surface*)malloc(sizeof(*(res1->surface)));
	res2->surface = (t_surface*)malloc(sizeof(*(res2->surface)));
	ft_memcpy(res1->surface, base_tmp->surface, sizeof(*base_tmp->surface));
	ft_memcpy(res2->surface, base_tmp->surface, sizeof(*base_tmp->surface));
	diff = t_vec3d_sub(div_pos, &base_tmp->surface->plane.pos);
	vertical_divide_fill_new_node_from_old_node(base_tmp, res1, &diff, 1);
	vertical_divide_fill_new_node_from_old_node(base_tmp, res2, &diff, 0);
	if (base_tmp->initial_surface)
		free(base_tmp->surface);
	free(*base_node);
	*base_node = NULL;
	if (res1->rear || res1->front || res2->front || res2->rear)
	{
		ft_printf("bsp_divide_surface error!\n");
		return (1);
	}
	return (0);
}

static int		horizontal_divide_fill_new_node_from_old_node(
					t_bsp_node *base_node,
					t_bsp_node *new_node,
					double v_diff,
					char flag_first)
{
	if (flag_first)
		new_node->surface->height = v_diff;
	else
	{
		new_node->surface->plane.pos.y += v_diff;
		new_node->surface->height -= v_diff;
	}
	if (new_node->surface->visual_type == evtTexture)
		bsp_hor_divide_texture(base_node->surface, v_diff, new_node->surface,
			flag_first);
	if (base_node->initial_surface)
		new_node->initial_surface = base_node->initial_surface;
	else
		new_node->initial_surface = base_node->surface;
	new_node->front = NULL;
	new_node->rear = NULL;
	return (0);
}

static int		bsp_horizontally_divide_vertical_node(
					t_bsp_node **base_node,
					double intersection_y,
					t_bsp_node *res1, t_bsp_node *res2)
{
	t_bsp_node	*base_tmp;
	double		vert_diff;

	vert_diff = intersection_y - (*base_node)->surface->plane.pos.y;
	base_tmp = *base_node;
	res1->surface = (t_surface*)malloc(sizeof(*(res1->surface)));
	res2->surface = (t_surface*)malloc(sizeof(*(res2->surface)));
	ft_memcpy(res1->surface, base_tmp->surface, sizeof(*base_tmp->surface));
	ft_memcpy(res2->surface, base_tmp->surface, sizeof(*base_tmp->surface));
	horizontal_divide_fill_new_node_from_old_node(base_tmp, res1, vert_diff, 1);
	horizontal_divide_fill_new_node_from_old_node(base_tmp, res2, vert_diff, 0);
	if (base_tmp->initial_surface)
		free(base_tmp->surface);
	free(*base_node);
	*base_node = NULL;
	if (res1->rear || res1->front || res2->front || res2->rear)
	{
		ft_printf("bsp_divide_surface error!\n");
		return (1);
	}
	return (0);
}

int				bsp_divide_node(
					t_bsp_node **base_node,
					const t_ray *div,
					t_bsp_node *res1, t_bsp_node *res2)
{
	if (base_node == NULL || *base_node == NULL || div == NULL ||
		res1 == NULL || res2 == NULL || (*base_node)->surface == NULL ||
		fabs((*base_node)->surface->plane.norm.y) > DBL_ZERO)
		return (1);
	else if (fabs(div->dir.y) > DBL_ZERO)
		return (bsp_vertically_divide_vertical_node(base_node, &div->pos,
					res1, res2));
	else
		return (bsp_horizontally_divide_vertical_node(base_node, div->pos.y,
					res1, res2));
}
