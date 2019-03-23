/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_of_occupied.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 10:11:56 by adzikovs          #+#    #+#             */
/*   Updated: 2018/11/20 10:27:07 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common_typedefs.h"

int		find_next_first_occupied_point(int x, t_list *occupied)
{
	while (occupied)
	{
		if (x <= ((int*)occupied->data)[0])
			return (((int*)occupied->data)[0]);
		else if (((int*)occupied->data)[0] <= x &&
					x <= ((int*)occupied->data)[1])
			return (x);
		occupied = occupied->next;
	}
	return (MAX_WINDOW_WIDTH);
}

t_list	*find_occupied_segment(t_list *occupied, int x)
{
	while (occupied)
	{
		if (((int*)occupied->data)[0] <= x &&
			x <= ((int*)occupied->data)[1])
			return (occupied);
		occupied = occupied->next;
	}
	return (NULL);
}

void	join_occupied_segments(t_list **tmp, t_list **tmp2)
{
	if ((*tmp2)->next != (*tmp))
		ft_printf("%$move_to_the_end: join error!\n", 2);
	else
	{
		(*tmp2)->next = (*tmp)->next;
		((int*)(*tmp2)->data)[1] = ((int*)(*tmp)->data)[1];
		free((*tmp)->data);
		free((*tmp));
		(*tmp) = (*tmp2);
	}
}

int		move_to_the_end_of_occupied_segment(int x[4], double t_crd[3],
			t_texturing_data *line, t_list *occupied)
{
	t_list	*tmp;
	t_list	*tmp2;
	int		diff;

	tmp = find_occupied_segment(occupied, x[0]);
	if (tmp == NULL)
		return (1);
	((int*)tmp->data)[0] = x[2];
	tmp2 = find_occupied_segment(occupied, x[2] - 1);
	if (tmp2)
		join_occupied_segments(&tmp, &tmp2);
	diff = ((int*)tmp->data)[1] + 1 - x[0];
	x[0] += diff;
	t_crd[0] += diff * line->x_z[1];
	t_crd[1] += diff * line->y_z[1];
	t_crd[2] += diff * line->one_z[1];
	x[2] = x[0];
	x[3] = find_next_first_occupied_point(x[0], occupied);
	return (0);
}
