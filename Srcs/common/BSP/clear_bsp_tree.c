/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_bsp_tree.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 11:15:08 by adzikovs          #+#    #+#             */
/*   Updated: 2018/11/07 11:15:46 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common_typedefs.h"

void	clear_bsp_tree(t_bsp_node **node)
{
	if (node && *node)
	{
		if ((*node)->initial_surface && (*node)->surface)
		{
			free((*node)->surface);
			(*node)->surface = NULL;
		}
		clear_bsp_tree(&(*node)->front);
		clear_bsp_tree(&(*node)->rear);
		free(*node);
		*node = NULL;
	}
}
