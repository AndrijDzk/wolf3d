/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proceed_bsp_node.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/19 11:10:28 by adzikovs          #+#    #+#             */
/*   Updated: 2018/10/20 14:27:49 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_vec3d_math.h"

#include "common.h"

static int	check_and_prepare_node(t_bsp_node *node,
					t_list **front, t_list **rear, t_list **all)
{
	if (node == NULL || node->surface == NULL || node->rear != NULL)
		return (1);
	if (front == NULL || rear == NULL || all == NULL)
		return (1);
	*all = (t_list*)node->front;
	node->front = NULL;
	*front = NULL;
	*rear = NULL;
	return (0);
}

static int	proceed_surfaces_in_list(t_bsp_node *node,
					t_list **front, t_list **rear, t_list **all)
{
	t_list	*tmp;

	if (node == NULL || front == NULL || rear == NULL || all == NULL)
		return (1);
	tmp = *all;
	while (tmp)
	{
		if (tmp->size == sizeof(t_surface))
			bsp_proceed_surface(node, (t_surface*)tmp->data, front, rear);
		else if (tmp->size == sizeof(t_bsp_node))
			bsp_proceed_node(node, (t_bsp_node**)&tmp->data, front, rear);
		else
		{
			ft_printf("%$proceed_bsp_node: unknown data in list!\n", 2);
			free(tmp->data);
			tmp->data = NULL;
			tmp->size = 0;
		}
		tmp = tmp->next;
	}
	return (0);
}

static int	bsp_create_new_node(t_bsp_node **new_node, t_list **surfaces)
{
	if (new_node == NULL || surfaces == NULL || *surfaces == NULL)
		return (1);
	if ((*surfaces)->size == sizeof(t_surface))
	{
		*new_node = (t_bsp_node*)malloc(sizeof(*new_node));
		(*new_node)->surface = (*surfaces)->data;
		(*new_node)->initial_surface = NULL;
		(*new_node)->rear = NULL;
	}
	else if ((*surfaces)->size == sizeof(t_bsp_node))
	{
		*new_node = (*surfaces)->data;
		if ((*new_node)->rear)
			ft_printf("bsp_create_new_node error!\n");
		(*surfaces)->data = NULL;
	}
	else
	{
		ft_printf("%$bsp_create_new_node: unknown data in list!\n", 2);
		return (1);
	}
	(*new_node)->front = (t_bsp_node*)(*surfaces)->next;
	free(*surfaces);
	*surfaces = NULL;
	return (0);
}

static int	create_new_nodes(t_bsp_node *node, t_list **front, t_list **rear)
{
	if (node == NULL || front == NULL || rear == NULL)
	{
		ft_printf("create_new_nodes error!\n");
		return (1);
	}
	node->front = NULL;
	node->rear = NULL;
	if (*front && bsp_create_new_node(&node->front, front))
		return (1);
	if (*rear && bsp_create_new_node(&node->rear, rear))
		return (1);
	if (node->front && node->front->rear)
		ft_printf("create_new_nodes error!\n");
	if (node->rear && node->rear->rear)
		ft_printf("create_new_nodes error!\n");
	return (0);
}

int			bsp_proceed_stack_elem(t_bsp_node *node)
{
	t_list	*front;
	t_list	*rear;
	t_list	*all;

	if (check_and_prepare_node(node, &front, &rear, &all))
	{
		ft_printf("check and prepare error!\n");
		check_and_prepare_node(node, &front, &rear, &all);
		return (1);
	}
	if (proceed_surfaces_in_list(node, &front, &rear, &all))
	{
		ft_printf("proceed surfaces in list error!\n");
		return (1);
	}
	t_list_non_deep_clear(&all);
	if (create_new_nodes(node, &front, &rear))
	{
		ft_printf("create_new_nodes error!\n");
		t_list_non_deep_clear(&front);
		t_list_non_deep_clear(&rear);
		return (1);
	}
	return (0);
}
