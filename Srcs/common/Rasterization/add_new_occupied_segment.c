/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_new_occupied_segment.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 12:18:13 by adzikovs          #+#    #+#             */
/*   Updated: 2018/11/23 12:18:13 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common_typedefs.h"

void		insert_new_occupied_segment(t_list **occupied, int x[4])
{
	t_list	*tmp;

	tmp = *occupied;
	*occupied = (t_list*)malloc(sizeof(**occupied));
	(*occupied)->size = sizeof(int) * 2;
	(*occupied)->data = (int*)malloc((*occupied)->size);
	((int*)(*occupied)->data)[0] = x[2];
	((int*)(*occupied)->data)[1] = x[1] - 1;
	(*occupied)->next = tmp;
}

int			add_new_occupied_segment(t_list **occupied, int x[4])
{
	if (x[2] >= x[1])
		return (0);
	while (*occupied)
	{
		if (x[2] <= ((int*)(*occupied)->data)[0] &&
			((int*)(*occupied)->data)[0] <= x[1])
		{
			((int*)(*occupied)->data)[0] = x[2];
			return (0);
		}
		else if (x[2] <= (((int*)(*occupied)->data)[1] + 1) &&
				((int*)(*occupied)->data)[1] <= (x[1] - 1))
		{
			((int*)(*occupied)->data)[1] = x[1] - 1;
			return (0);
		}
		else if (x[2] <= ((int*)(*occupied)->data)[0])
			break ;
		occupied = &((*occupied)->next);
	}
	insert_new_occupied_segment(occupied, x);
	return (0);
}
