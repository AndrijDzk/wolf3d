/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_surface_into_tree.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 09:47:43 by adzikovs          #+#    #+#             */
/*   Updated: 2018/11/23 10:19:33 by adzikovs         ###   ########.fr       */
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

int				bsp_divide_and_insert_surface_into_tree(t_bsp_node **root,
					t_surface *surface, t_ray *div)
{
	t_bsp_node	*n1;
	t_bsp_node	*n2;

	if (root == NULL || surface == NULL || div == NULL)
		return (1);
	n1 = (t_bsp_node*)malloc(sizeof(*n1));
	n2 = (t_bsp_node*)malloc(sizeof(*n2));
	if (bsp_divide_surface(surface, div, n1, n2))
		return (bsp_divide_and_insert_error_exit(n1, n2, NULL, NULL));
	if (bsp_check_new_nodes(root, n1, n2))
		return (bsp_divide_and_insert_error_exit(NULL, NULL, &n1, &n2));
	if (bsp_insert_node_into_tree(root, &n1))
		return (bsp_divide_and_insert_error_exit(NULL, NULL, &n1, &n2));
	if (bsp_insert_node_into_tree(root, &n2))
		return (bsp_divide_and_insert_error_exit(NULL, NULL, NULL, &n2));
	return (0);
}

int				bsp_insert_surface_into_tree_without_divide(t_bsp_node **root,
					t_surface *surface)
{
	if (root == NULL || (*root && (*root)->surface == NULL) || surface == NULL)
		return (1);
	if (get_surface_surface_rel_pos((*root)->surface, surface) >= 0)
		return (bsp_insert_surface_into_tree(&(*root)->front, surface));
	else
		return (bsp_insert_surface_into_tree(&(*root)->rear, surface));
}

int				bsp_insert_surface_into_tree(t_bsp_node **root,
					t_surface *surface)
{
	t_ray		div;

	if (root == NULL || surface == NULL ||
		(*root && (*root)->surface == NULL))
		return (1);
	if (*root == NULL)
	{
		*root = (t_bsp_node*)malloc(sizeof(**root));
		(*root)->surface = surface;
		(*root)->initial_surface = NULL;
		(*root)->front = NULL;
		(*root)->rear = NULL;
		return (0);
	}
	if (bsp_divide_is_necessary((*root)->surface, surface, &div))
		return (bsp_divide_and_insert_surface_into_tree(root, surface, &div));
	else
		return (bsp_insert_surface_into_tree_without_divide(root, surface));
}
