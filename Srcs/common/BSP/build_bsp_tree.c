/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_bsp_tree.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 16:08:01 by adzikovs          #+#    #+#             */
/*   Updated: 2018/11/20 12:09:56 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

/*
**static int		init_stack(t_list **stack, t_list *surfaces)
**{
**	t_bsp_node	*root;
**
**	if (stack == NULL || surfaces == NULL || surfaces->data == NULL ||
**		surfaces->size != sizeof(t_surface))
**		return (1);
**	root = (t_bsp_node*)malloc(sizeof(*root));
**	*stack = new_t_list_node(root, sizeof(*root));
**	root->surface = (t_surface*)surfaces->data;
**	root->initial_surface = NULL;
**	root->front = (t_bsp_node*)t_list_non_deep_copy(surfaces->next);
**	root->rear = NULL;
**	return (0);
**}
**
**static void		*error_exit(t_list *stack, t_bsp_node **root)
**{
**	ft_printf("build_bsp_tree: proceed_stack_elem error!\n");
**	clear_build_bsp_stack(&stack);
**	clear_bsp_tree(root);
**	return (NULL);
**}
**
**t_bsp_node		*build_bsp_tree_from_t_list(t_list *surfaces)
**{
**	t_list		*stack;
**	t_list		*tmp;
**	t_bsp_node	*root;
**	t_bsp_node	*tmp2;
**
**	if (init_stack(&stack, surfaces))
**		return (NULL);
**	root = (t_bsp_node*)stack->data;
**	while (stack)
**	{
**		tmp = stack;
**		stack = stack->next;
**		tmp2 = (t_bsp_node*)tmp->data;
**		if (bsp_proceed_stack_elem(tmp2))
**			return (error_exit(stack, &root));
**		free(tmp);
**		if (tmp2->front)
**			t_list_push_front(&stack, tmp2->front, sizeof(*(tmp2->front)));
**		if (tmp2->rear)
**			t_list_push_front(&stack, tmp2->rear, sizeof(*(tmp2->rear)));
**	}
**	return (root);
**}
*/

t_bsp_node	*build_bsp_tree_from_t_list(t_list *surfaces)
{
	t_bsp_node	*root;
	t_list		*tmp;

	root = NULL;
	tmp = surfaces;
	while (tmp)
	{
		if (fabs(((t_surface*)tmp->data)->plane.norm.y) > DBL_ZERO)
			bsp_insert_surface_into_tree(&root, (t_surface*)tmp->data);
		tmp = tmp->next;
	}
	tmp = surfaces;
	while (tmp)
	{
		if (fabs(((t_surface*)tmp->data)->plane.norm.y) <= DBL_ZERO)
			bsp_insert_surface_into_tree(&root, (t_surface*)tmp->data);
		tmp = tmp->next;
	}
	return (root);
}

t_bsp_node	*build_bsp_tree(t_scene *scene)
{
	if (scene == NULL)
		return (NULL);
	if (scene->cont_type == Cont_t_list)
		return (build_bsp_tree_from_t_list(scene->container.l_surfaces));
	else
		return (NULL);
}

static int	rebuild_bsp_tree_from_t_list(t_scene *scene)
{
	t_bsp_node		*tmp;

	tmp = build_bsp_tree(scene);
	if (tmp == NULL)
		return (1);
	clear_bsp_tree(&scene->bsp_tree);
	scene->bsp_tree = tmp;
	return (0);
}

int			rebuild_bsp_tree(t_scene *scene)
{
	if (scene == NULL)
		return (1);
	if (scene->cont_type == Cont_t_list)
		return (rebuild_bsp_tree_from_t_list(scene));
	else
		return (1);
}
