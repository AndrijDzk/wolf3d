/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gj_elimination_correct_diagonal.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 12:48:49 by adzikovs          #+#    #+#             */
/*   Updated: 2018/11/07 12:49:06 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "common_typedefs.h"

int		correct_diagonal(double m[4][4], double res[4][4])
{
	size_t		i;
	size_t		j;
	double		div;

	i = 0;
	while (i < 4)
	{
		if (fabs(m[i][i]) <= DBL_ZERO)
			return (1);
		else if (fabs(m[i][i] - 1) > DBL_ZERO)
		{
			div = m[i][i];
			j = 0;
			while (j < 4)
			{
				m[i][j] = m[i][j] / div;
				res[i][j] = res[i][j] / div;
				j++;
			}
		}
		i++;
	}
	return (0);
}
