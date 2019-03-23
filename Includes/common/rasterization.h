/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rasterization.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/11 13:33:16 by adzikovs          #+#    #+#             */
/*   Updated: 2018/11/24 11:47:25 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RASTERIZATION_H
# define RASTERIZATION_H

# include "common_typedefs.h"

int					rasterization_get_vertex_crd(const t_surface *surface,
						t_vec3d vertexes[4]);

int					rasterization_get_vertex_projections(
						t_vec3d vertexes[4],
						t_vec3d proj_data[8],
						t_vec3d *proj_pointers[8]);

void				project_vertex_on_screen(t_camera *camera, t_vec3d *v);

int					init_texture_crd(const char flag, const double coeff,
						const unsigned vertex_num, t_texturing_data *res);

int					approximate_texturing_data_along_line(
						t_texturing_data *data);

void				perspective_divide(t_vec3d *point,
						const int *focal_length);

int					project_segment(
						t_camera *camera,
						t_vec3d segment[5][2],
						t_textured_2d_segment *res,
						unsigned vert_num);

int					project_out_of_sight_side(
						t_vec3d vertexes[5][2],
						t_textured_2d_segment *res_ptrs[5]);

void				get_texture_projection(
						t_camera *camera,
						t_vec3d vertexes[4],
						t_textured_2d_segment *res_ptrs[5]);

int					find_borders_for_y(
						double y,
						t_textured_2d_segment *borders[2][5],
						t_textured_2d_segment **res_left,
						t_textured_2d_segment **res_right);

int					fill_entry_with_left_border_data(int y,
						t_texturing_data *res,
						t_textured_2d_segment *left_border);

int					fill_entry_with_right_border_data(int y,
						t_texturing_data *res,
						t_textured_2d_segment *right_border);

int					fill_texturing_table(
						t_texturing_table *res,
						t_textured_2d_segment *borders[2][5]);

t_texturing_table	*calculate_texturing_data(
						char order, t_sdl *sdl,
						t_textured_2d_segment *segments[5]);

int					find_next_first_occupied_point(int x, t_list *occupied);

t_list				*find_occupied_segment(t_list *occupied, int x);

int					add_new_occupied_segment(t_list **occupied, int x[4]);

int					move_to_the_end_of_occupied_segment(
						int x[4], double t_crd[3],
						t_texturing_data *line, t_list *occupied);

void				draw_texture_line(t_sdl *sdl, t_xpm_texture *txt, int y,
						t_texturing_data *line);

void				*draw_texture_multithreaded_slave(void *param);

int					draw_texture_multithreaded(char order, t_sdl *sdl,
						t_textured_2d_segment *segments[5],
						t_xpm_texture *txt);

int					draw_texture(t_sdl *sdl, t_xpm_texture *txt,
						t_texturing_table *table);

int					render_texture_rasterization(t_sdl *sdl, t_camera *camera,
						t_surface *surface);

int					render_surface_rasterization(t_sdl *sdl, t_camera *camera,
						t_surface *surface);

void				*renderer_scene_rasterization(t_sdl *sdl, t_scene *scene,
						t_camera *camera);

#endif
