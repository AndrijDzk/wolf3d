/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hor_and_vert_surfaces_intersection.c               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/31 14:08:21 by adzikovs          #+#    #+#             */
/*   Updated: 2018/11/21 13:18:09 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

#include "math_3d.h"

#include "intersections.h"

t_2d_segment	vertexes_into_2d_segment(const t_vec2d *v1, const t_vec2d *v2)
{
	t_2d_segment	res;

	res.a = v2->x - v1->x;
	res.b = v1->y - v2->y;
	res.c = -v1->y * res.a - v2->x * res.b;
	res.x[0] = v1->x;
	res.x[1] = v2->x;
	res.y[0] = v1->y;
	res.y[1] = v2->y;
	return (res);
}

int				surface_into_quad(const t_surface *s, t_2d_segment quad[4])
{
	t_vec2d		v1;
	t_vec2d		v2;

	if (s == NULL)
		return (1);
	v1.x = s->plane.pos.x;
	v1.y = s->plane.pos.z;
	v2.x = v1.x + s->length;
	v2.y = v1.x;
	quad[0] = vertexes_into_2d_segment(&v1, &v2);
	v1 = v2;
	v2.y += s->height;
	quad[1] = vertexes_into_2d_segment(&v1, &v2);
	v1 = v2;
	v2.x -= s->length;
	quad[2] = vertexes_into_2d_segment(&v1, &v2);
	v1 = v2;
	v2.y -= s->height;
	quad[3] = vertexes_into_2d_segment(&v1, &v2);
	return (0);
}

static int		check_vertical(const t_surface *s1, const t_surface *s2)
{
	const t_surface		*vert;
	double				y;

	if (fabs(s1->plane.norm.y) > DBL_ZERO)
	{
		y = s1->plane.pos.y;
		vert = s2;
	}
	else
	{
		vert = s1;
		y = s2->plane.pos.y;
	}
	return (check_limits(vert->plane.pos.y, vert->height, y));
}

/*
**static void		convert_res_into_3d(
**					const t_surface *s1,
**					const t_surface *s2,
**					const t_vec2d *res_2d,
**					t_vec3d *res)
**{
**	if (res)
**	{
**		if (fabs(s1->plane.norm.y) > DBL_ZERO)
**			*res = t_vec2d_into_t_vec3d(*res_2d, s1->plane.pos.y);
**		else
**			*res = t_vec2d_into_t_vec3d(*res_2d, s2->plane.pos.y);
**	}
**}
*/

int				horizontal_and_vertical_surfaces_intersection(
					const t_surface *s1, const t_surface *s2,
					t_vec3d *res)
{
	if (s1 == NULL || s2 == NULL)
		return (0);
	if (check_vertical(s1, s2) == 0)
		return (0);
	else if (res)
	{
		if (fabs(s1->plane.norm.y) >= DBL_ZERO)
			ft_memcpy(res, &s1->plane.pos, sizeof(*res));
		else
			ft_memcpy(res, &s2->plane.pos, sizeof(*res));
		return (1);
	}
	else
		return (1);
}

/*
**int				horizontal_and_vertical_surfaces_intersection(
**					const t_surface *s1, const t_surface *s2,
**					t_vec3d *res)
**{
**	t_2d_segment	quad[4];
**	t_2d_segment	seg;
**	t_vec2d			res_tmp;
**
**	if (s1 == NULL || s2 == NULL)
**		return (0);
**	if (check_vertical(s1, s2) == 0)
**		return (0);
**	if (fabs(s1->plane.norm.y) > DBL_ZERO)
**		surface_into_quad(s1, quad);
**	else
**		surface_into_quad(s2, quad);
**	if (fabs(s1->plane.norm.y) > DBL_ZERO)
**		seg = surface_into_2d_segment(s2);
**	else
**		seg = surface_into_2d_segment(s1);
**	if (segment_quad_intersection(quad, &seg, &res_tmp) ||
**		segment_lies_on_quad_edge(quad, &seg, &res_tmp) ||
**		segment_inside_quad(quad, &seg, &res_tmp))
**	{
**		convert_res_into_3d(s1, s2, &res_tmp, res);
**		return (1);
**	}
**	return (0);
**}
*/
