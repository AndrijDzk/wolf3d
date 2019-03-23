/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_ray_color.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 14:34:19 by adzikovs          #+#    #+#             */
/*   Updated: 2018/11/07 14:34:19 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "intersections.h"

SDL_Color	get_ray_color(t_scene *scene, t_ray const *ray)
{
	double		min_dist;
	double		tmp_dist;
	SDL_Color	res;
	t_list		*list;

	ft_memset(&res, 0, sizeof(res));
	if (scene->cont_type != Cont_t_list)
		return (res);
	list = scene->container.l_surfaces;
	min_dist = -1;
	while (list)
	{
		tmp_dist = ray_surface_intersection(ray, list->data);
		if (tmp_dist > 0 && (tmp_dist < min_dist || min_dist < 0) &&
		((t_surface*)(list->data))->visual_type == evtColor)
		{
			min_dist = tmp_dist;
			res = ((t_surface*)(list->data))->visual.color;
		}
		list = list->next;
	}
	return (res);
}
