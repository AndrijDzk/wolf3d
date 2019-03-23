/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_new_nodes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 10:22:06 by adzikovs          #+#    #+#             */
/*   Updated: 2018/11/22 10:22:06 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsp.h"

int		bsp_check_new_nodes(t_bsp_node **root,
			t_bsp_node *n1, t_bsp_node *n2)
{
	if (root == NULL || *root == NULL)
		return (1);
	if (n1 &&
		bsp_divide_is_necessary((*root)->surface, n1->surface, NULL))
	{
		ft_printf("%$n1 requires unnecessary divide!\n", 2);
		bsp_divide_is_necessary((*root)->surface, n1->surface, NULL);
		return (1);
	}
	if (n2 &&
		bsp_divide_is_necessary((*root)->surface, n2->surface, NULL))
	{
		ft_printf("%$n2 requires unnecessary divide!\n", 2);
		bsp_divide_is_necessary((*root)->surface, n2->surface, NULL);
		return (1);
	}
	return (0);
}
