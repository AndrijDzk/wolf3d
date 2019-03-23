/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_left_and_right_borders.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 15:19:51 by adzikovs          #+#    #+#             */
/*   Updated: 2018/11/13 10:17:59 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common_typedefs.h"

int		get_left_and_right_borders(
			t_textured_2d_segment *segments[5],
			char order,
			t_textured_2d_segment *left[5],
			t_textured_2d_segment *right[5])
{
	size_t		i;
	size_t		j;
	size_t		k;

	ft_bzero(left, sizeof(*left) * 5);
	ft_bzero(right, sizeof(*right) * 5);
	j = 0;
	k = 0;
	i = 0;
	while (i < 5)
	{
		if (segments[i])
		{
			if ((segments[i]->segment.b > 0 && order > 0) ||
				(segments[i]->segment.b < 0 && order <= 0))
				left[j++] = segments[i];
			else if (segments[i]->segment.b)
				right[k++] = segments[i];
		}
		i++;
	}
	return (0);
}
