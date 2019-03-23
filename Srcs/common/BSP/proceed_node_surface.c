/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proceed_node_surface.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/19 15:10:51 by adzikovs          #+#    #+#             */
/*   Updated: 2018/11/07 11:39:37 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_vec3d_math.h"

#include "common.h"

static int	proceed_surface_without_divide(t_bsp_node *node, t_surface *surface,
			t_list **front, t_list **rear)
{
	double		rel_pos;

	if (surface == NULL || node == NULL || node->surface == NULL)
		return (1);
	rel_pos = get_surface_surface_rel_pos(node->surface, surface);
	if (rel_pos >= 0)
		t_list_push_back(front, surface, sizeof(*surface));
	else
		t_list_push_back(rear, surface, sizeof(*surface));
	return (0);
}

static int	proceed_node_without_divide(t_bsp_node *base_node,
				t_bsp_node *moving_node, t_list **front, t_list **rear)
{
	double		rel_pos;

	if (moving_node == NULL ||
		base_node == NULL || base_node->surface == NULL)
		return (1);
	rel_pos = get_surface_surface_rel_pos(base_node->surface,
		moving_node->surface);
	if (moving_node->front || moving_node->rear)
		ft_printf("proceed_node_without_divide error!\n");
	if (rel_pos >= 0)
		t_list_push_back(front, moving_node, sizeof(*moving_node));
	else
		t_list_push_back(rear, moving_node, sizeof(*moving_node));
	return (0);
}

int			bsp_proceed_surface(t_bsp_node *node, t_surface *surface,
				t_list **front, t_list **rear)
{
	t_ray		div;
	t_bsp_node	*new1;
	t_bsp_node	*new2;

	if (surface == NULL || node == NULL || node->surface == NULL)
		return (1);
	if (bsp_divide_is_necessary(node->surface, surface, &div))
	{
		new1 = (t_bsp_node*)malloc(sizeof(*new1));
		new2 = (t_bsp_node*)malloc(sizeof(*new2));
		if (bsp_divide_surface(surface, &div, new1, new2) ||
			proceed_node_without_divide(node, new1, front, rear) ||
			proceed_node_without_divide(node, new2, front, rear))
			ft_printf("%$BSP proceed_surface: divide error!\n", 2);
	}
	else
		return (proceed_surface_without_divide(node, surface, front, rear));
	return (0);
}

int			bsp_proceed_node(t_bsp_node *node, t_bsp_node **moving_node,
				t_list **front, t_list **rear)
{
	t_ray		div;
	t_bsp_node	*new1;
	t_bsp_node	*new2;

	if (moving_node == NULL || *moving_node == NULL ||
		(*moving_node)->surface == NULL ||
		node == NULL || node->surface == NULL)
		return (1);
	if (bsp_divide_is_necessary(node->surface, (*moving_node)->surface, &div))
	{
		new1 = (t_bsp_node*)malloc(sizeof(*new1));
		new2 = (t_bsp_node*)malloc(sizeof(*new2));
		if (bsp_divide_node(moving_node, &div, new1, new2) ||
			proceed_node_without_divide(node, new1, front, rear) ||
			proceed_node_without_divide(node, new2, front, rear))
			ft_printf("%$BSP proceed_node: divide error!\n", 2);
	}
	else
		return (proceed_node_without_divide(node, *moving_node, front, rear));
	return (0);
}
