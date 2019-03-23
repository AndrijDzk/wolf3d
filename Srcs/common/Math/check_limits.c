/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_limits.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/18 10:46:54 by adzikovs          #+#    #+#             */
/*   Updated: 2018/11/18 10:46:54 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "common_typedefs.h"

char			check_limits(double l1, double l2, double val)
{
	if (fabs(l1 - l2) < DBL_ZERO)
	{
		l1 -= DBL_ZERO;
		l2 += DBL_ZERO;
	}
	if (l1 < l2)
	{
		if (val < l1 || l2 < val)
			return (0);
		else
			return (1);
	}
	else
	{
		if (val < l2 || l1 < val)
			return (0);
		else
			return (1);
	}
}

char			check_limits_inclusive(double l1, double l2, double val)
{
	if (check_limits(l1, l2, val))
		return (1);
	else if (fabs(val - l1) <= DBL_ZERO)
		return (1);
	else if (fabs(val - l2) <= DBL_ZERO)
		return (1);
	else
		return (0);
}
