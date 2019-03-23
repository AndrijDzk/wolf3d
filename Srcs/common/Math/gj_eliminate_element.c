/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gj_eliminate_element.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 12:55:00 by adzikovs          #+#    #+#             */
/*   Updated: 2018/11/07 12:55:00 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix_math.h"

static int		select_row_for_add(
					double m[4][4],
					size_t i,
					size_t j,
					size_t *res)
{
	size_t		k;
	double		mult;

	k = j;
	while (k < 4)
	{
		if (k != i && fabs(m[k][j]) > DBL_ZERO)
		{
			mult = -m[i][j] / m[k][j];
			if (fabs(m[i][i] + m[k][i] * mult) > DBL_ZERO)
			{
				*res = k;
				return (0);
			}
		}
		k++;
	}
	return (1);
}

int				gj_eliminate_element(
					double copy[4][4],
					size_t i,
					size_t j,
					double res[4][4])
{
	size_t		k;
	double		mult;

	if (i != j && fabs(copy[i][j]) > DBL_ZERO)
	{
		if (select_row_for_add(copy, i, j, &k))
			return (1);
		mult = -copy[i][j] / copy[k][j];
		add_rows(copy, i, k, mult);
		add_rows(res, i, k, mult);
	}
	return (0);
}
