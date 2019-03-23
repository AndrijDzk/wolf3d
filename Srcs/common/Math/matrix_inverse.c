/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_inverse.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/27 10:38:03 by adzikovs          #+#    #+#             */
/*   Updated: 2018/11/07 12:54:33 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "common_typedefs.h"

#include "matrix_math.h"

static void		init_res(double res[4][4])
{
	size_t		i;
	size_t		j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			if (i == j)
				res[i][j] = 1;
			else
				res[i][j] = 0;
			j++;
		}
		i++;
	}
}

static int		prepare_row(double m[4][4], size_t i, double res[4][4])
{
	size_t		j;

	j = 0;
	while (j < 4)
	{
		if (fabs(m[j][i]) > DBL_ZERO && (j != i))
		{
			add_rows(m, i, j, 1);
			add_rows(res, i, j, 1);
			return (0);
		}
		j++;
	}
	return (1);
}

static int		check_and_prepare(double m[4][4], double res[4][4])
{
	size_t		i;

	i = 0;
	while (i < 4)
	{
		if (fabs(m[i][i]) <= DBL_ZERO)
		{
			if (prepare_row(m, i, res))
				return (1);
		}
		i++;
	}
	return (0);
}

int				matrix_inverse(double m[4][4], double res[4][4])
{
	double		copy[4][4];
	size_t		i;
	size_t		j;

	init_res(res);
	ft_memcpy(copy, m, sizeof(double) * 16);
	if (check_and_prepare(copy, res))
		return (1);
	j = 0;
	while (j < 4)
	{
		i = 0;
		while (i < 4)
		{
			gj_eliminate_element(copy, i, j, res);
			i++;
		}
		j++;
	}
	if (correct_diagonal(copy, res))
		return (1);
	else
		return (0);
}
