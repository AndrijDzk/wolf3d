/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_bsp_stack.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 11:19:33 by adzikovs          #+#    #+#             */
/*   Updated: 2018/11/07 11:19:33 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common_typedefs.h"

static void		clear_node_unprocessed_elements(t_list **elems)
{
	t_list		*tmp;
	t_bsp_node	*node_tmp;

	while (elems && *elems)
	{
		tmp = (*elems)->next;
		if ((*elems)->size == sizeof(t_bsp_node))
		{
			node_tmp = (t_bsp_node*)(*elems)->data;
			if (node_tmp->initial_surface && node_tmp->surface)
			{
				free(node_tmp->surface);
				node_tmp->surface = NULL;
			}
			free((*elems)->data);
			(*elems)->data = NULL;
			(*elems)->size = 0;
		}
		free(*elems);
		*elems = tmp;
	}
}

void			clear_build_bsp_stack(t_list **stack)
{
	t_list		*tmp;
	t_bsp_node	*node_tmp;

	while (stack && *stack)
	{
		tmp = (*stack)->next;
		if ((*stack)->size == sizeof(t_bsp_node))
		{
			node_tmp = (t_bsp_node*)(*stack)->data;
			clear_node_unprocessed_elements((t_list**)&node_tmp->front);
		}
		free(*stack);
		*stack = tmp;
	}
}
