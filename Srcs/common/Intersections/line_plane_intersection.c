/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_plane_intersection.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/25 15:30:59 by adzikovs          #+#    #+#             */
/*   Updated: 2018/11/07 11:44:37 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include <math.h>

#include "math_3d.h"

#include "t_vec3d_math.h"

#include "common.h"

double			test_intersection_point(t_ray const *ray, double t,
					t_surface const *surface)
{
	double		x;
	double		y;
	double		z;
	double		end;

	if (surface->inf || t < 0)
		return (t);
	end = surface->plane.pos.x + surface->length * surface->plane.norm.z;
	x = ray->pos.x + ray->dir.x * t;
	if (!check_limits(surface->plane.pos.x, end, x))
		return (-1);
	end = surface->plane.pos.y + surface->height;
	y = ray->pos.y + ray->dir.y * t;
	if (!check_limits(surface->plane.pos.y, end, y))
		return (-1);
	end = surface->plane.pos.z - surface->length * surface->plane.norm.x;
	z = ray->pos.z + ray->dir.z * t;
	if (!check_limits(surface->plane.pos.z, end, z))
		return (-1);
	return (t);
}

double			ray_surface_intersection(t_ray const *ray,
					t_surface const *surface)
{
	t_vec3d	diff;
	double	numerator;
	double	denominator;
	double	t;

	denominator = t_vec3d_dot_product(&(ray->dir), &(surface->plane.norm));
	if (fabs(denominator) < DBL_ZERO)
		return (-1);
	diff = t_vec3d_sub(&(surface->plane.pos), &(ray->pos));
	numerator = t_vec3d_dot_product(&diff, &(surface->plane.norm));
	t = numerator / denominator;
	return (test_intersection_point(ray, t, surface));
}

int				line_plane_intersection(const t_ray *line,
						const t_plane *plane,
						t_vec3d *res)
{
	t_vec3d	diff;
	double	numerator;
	double	denominator;
	double	t;

	denominator = t_vec3d_dot_product(&line->dir, &plane->norm);
	if (fabs(denominator) < DBL_ZERO)
		return (0);
	diff = t_vec3d_sub(&plane->pos, &line->pos);
	numerator = t_vec3d_dot_product(&diff, &plane->norm);
	t = numerator / denominator;
	if (res)
	{
		*res = t_vec3d_scal_mult(&line->dir, t);
		*res = t_vec3d_add(res, &line->pos);
	}
	return (1);
}

int				ray_plane_intersection(const t_ray *ray,
						const t_plane *plane,
						t_vec3d *res)
{
	t_vec3d	diff;
	double	numerator;
	double	denominator;
	double	t;

	denominator = t_vec3d_dot_product(&ray->dir, &plane->norm);
	if (fabs(denominator) < DBL_ZERO)
		return (0);
	diff = t_vec3d_sub(&plane->pos, &ray->pos);
	numerator = t_vec3d_dot_product(&diff, &plane->norm);
	denominator = 1 / denominator;
	if ((t = numerator * denominator) < 0)
		return (0);
	if (res)
	{
		*res = t_vec3d_scal_mult(&ray->dir, t);
		*res = t_vec3d_add(res, &ray->pos);
	}
	return (1);
}
