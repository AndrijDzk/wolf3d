/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsp.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 10:11:20 by adzikovs          #+#    #+#             */
/*   Updated: 2018/11/07 11:15:46 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_BSP_H
# define WOLF3D_BSP_H

# include "common_typedefs.h"

int			rebuild_bsp_tree(t_scene *scene);

t_bsp_node	*build_bsp_tree_from_t_list(t_list *surfaces);

t_bsp_node	*build_bsp_tree(t_scene *scene);

void		clear_bsp_tree(t_bsp_node **node);

void		clear_build_bsp_stack(t_list **stack);

int			bsp_proceed_stack_elem(t_bsp_node *node);

int			bsp_hor_divide_texture(
				const t_surface *base_surface,
				double vert_diff,
				t_surface *new_surface,
				char flag_first);

int			bsp_vert_divide_texture(
				const t_surface *base_surface,
				const t_vec3d *diff,
				t_surface *new_surface,
				char flag_first);

int			bsp_divide_node(t_bsp_node **base_node, const t_ray *div,
				t_bsp_node *res1, t_bsp_node *res2);

int			bsp_divide_surface(t_surface *base_surface,
				const t_ray *div, t_bsp_node *res1, t_bsp_node *res2);

int			bsp_proceed_node(t_bsp_node *node, t_bsp_node **moving_node,
				t_list **front, t_list **rear);

int			bsp_proceed_surface(t_bsp_node *node, t_surface *surface,
				t_list **front, t_list **rear);

int			bsp_divide_is_necessary(const t_surface *base_surface,
				const t_surface *surface, t_ray *div);

int			bsp_check_new_nodes(t_bsp_node **root,
				t_bsp_node *n1, t_bsp_node *n2);

int			bsp_insert_node_into_tree(t_bsp_node **root,
				t_bsp_node **node);

int			bsp_insert_surface_into_tree(t_bsp_node **root,
				t_surface *surface);

int			remove_surface_from_bsp_tree(t_bsp_node **root,
				t_surface *initial_surface);

#endif
