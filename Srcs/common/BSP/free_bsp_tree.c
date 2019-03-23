/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_bsp_tree.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 09:46:04 by adzikovs          #+#    #+#             */
/*   Updated: 2018/11/07 11:32:27 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common_typedefs.h"

int		simple_shift(t_bsp_node **root, t_bsp_node *new_root)
{
	if (root == NULL || *root == NULL ||
		*root == new_root)
		return (1);
	if ((*root)->initial_surface && (*root)->surface)
		free((*root)->surface);
	free(*root);
	*root = new_root;
	return (0);
}

/*
**		if ((*root)->front && (*root)->rear == NULL)
**		{
**			if (simple_shift(root, (*root)->front))
**				return (1);
**		}
**		else if ((*root)->front == NULL && (*root)->rear)
**		{
**			if (simple_shift(root, (*root)->rear))
**				return (1);
**		}
**		else if ((*root)->front == NULL && (*root)->rear == NULL)
**		{
**			if (simple_shift(root, NULL))
**				return (1);
**		}
**		else
**			return (1);
*/

int		remove_surface_from_bsp_tree(t_bsp_node **root,
			t_surface *initial_surface)
{
	t_bsp_node		*tmp;

	while (root && *root && initial_surface &&
		((*root)->surface == initial_surface ||
		(*root)->initial_surface == initial_surface))
	{
		if ((*root)->front)
			tmp = (*root)->front;
		else
			tmp = (*root)->rear;
		if ((*root)->front && (*root)->rear)
			return (1);
		else
		{
			if (simple_shift(root, tmp))
				return (1);
		}
	}
	if (root == NULL || initial_surface == NULL)
		return (1);
	else if (*root == NULL)
		return (0);
	else if (remove_surface_from_bsp_tree(&(*root)->front, initial_surface))
		return (1);
	return (remove_surface_from_bsp_tree(&(*root)->rear, initial_surface));
}
