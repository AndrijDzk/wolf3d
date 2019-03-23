/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_into_tree.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/22 14:38:54 by adzikovs          #+#    #+#             */
/*   Updated: 2018/11/22 10:21:39 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

static int		bsp_divide_and_insert_error_exit(
					void *ptr1, void *ptr2,
					t_bsp_node **n1, t_bsp_node **n2)
{
	if (ptr1)
		free(ptr1);
	if (ptr2)
		free(ptr2);
	if (n1 && *n1)
		clear_bsp_tree(n1);
	if (n2 && *n2)
		clear_bsp_tree(n2);
	return (1);
}

int				bsp_divide_and_insert_node_into_tree(t_bsp_node **root,
					t_bsp_node **node, t_ray *div)
{
	t_bsp_node	*n1;
	t_bsp_node	*n2;

	if (root == NULL || node == NULL || *node == NULL || div == NULL)
		return (1);
	n1 = (t_bsp_node*)malloc(sizeof(*n1));
	n2 = (t_bsp_node*)malloc(sizeof(*n2));
	if (bsp_divide_node(node, div, n1, n2))
		return (bsp_divide_and_insert_error_exit(n1, n2, NULL, NULL));
	if (bsp_check_new_nodes(root, n1, n2))
		return (bsp_divide_and_insert_error_exit(NULL, NULL, &n1, &n2));
	if (bsp_insert_node_into_tree(root, &n1))
		return (bsp_divide_and_insert_error_exit(NULL, NULL, &n1, &n2));
	if (bsp_insert_node_into_tree(root, &n2))
		return (bsp_divide_and_insert_error_exit(NULL, NULL, NULL, &n2));
	return (0);
}

int				bsp_insert_node_into_tree_without_divide(t_bsp_node **root,
					t_bsp_node **node)
{
	if (root == NULL || (*root && (*root)->surface == NULL) ||
		node == NULL || *node == NULL || (*node)->surface == NULL)
		return (1);
	if (get_surface_surface_rel_pos((*root)->surface, (*node)->surface) >= 0)
		return (bsp_insert_node_into_tree(&(*root)->front, node));
	else
		return (bsp_insert_node_into_tree(&(*root)->rear, node));
}

int				bsp_insert_node_into_tree(
					t_bsp_node **root, t_bsp_node **node)
{
	t_ray		div;

	if (root == NULL || node == NULL || *node == NULL ||
			(*node)->surface == NULL ||
			(*root && (*root)->surface == NULL))
		return (1);
	if (*root == NULL)
	{
		*root = *node;
		return (0);
	}
	if (bsp_divide_is_necessary((*root)->surface, (*node)->surface, &div))
		return (bsp_divide_and_insert_node_into_tree(root, node, &div));
	else
		return (bsp_insert_node_into_tree_without_divide(root, node));
}
