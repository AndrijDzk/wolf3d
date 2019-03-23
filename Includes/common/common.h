/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/15 09:27:39 by adzikovs          #+#    #+#             */
/*   Updated: 2018/11/23 14:03:43 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMON_H
# define COMMON_H

# include "common_typedefs.h"

# include "camera.h"

# include "bsp.h"

# include "t_vec3d_math.h"

int						print_sdl_error_and_return(char *where);

int						check_and_draw_point(t_sdl *sdl, SDL_Color *c,
							int x, int y);

int						draw_point(t_sdl *sdl, SDL_Color *c, int x, int y);

int						draw_line(t_sdl *sdl, t_vec2d *start, t_vec2d *end,
							SDL_Color *color);

int						draw_rectangle(t_sdl *sdl, t_vec3d vertex[4],
							SDL_Color *color);

int						draw_polygon(t_sdl *sdl, t_vec3d *vertex[9],
							SDL_Color *color, char order);

SDL_Color				get_ray_color(t_scene *scene, t_ray const *ray);

void					*raycast_renderer_slave(void *param);

int						render_scene(t_sdl *sdl, t_scene *scene,
							t_camera *camera);

void					throw_current_image_on_screen(t_sdl *sdl);

int						process_mouse(t_sdl *sdl, t_scene *scene,
							t_camera *camera,
							SDL_Event *event);

int						camera_movement(t_sdl *sdl, t_scene *scene,
							t_camera *camera,
							enum e_input_action action);

int						change_fov(t_sdl *sdl, t_scene *scene,
							t_camera *camera, enum e_input_action action);

int						camera_matrix_inverse(double m[4][4],
							double m_inv[4][4]);

void					draw_crosshair(t_sdl *sdl);

int						read_xpm_header(int fd, t_xpm_header *res);

t_xpm_color				*read_xpm_colors(int fd, size_t am);

t_xpm_texture			*read_xpm_texture(char *filename);

int						draw_xpm_image(t_sdl *sdl, char *filename);

void					clear_window(t_sdl *sdl);

SDL_Color				*find_xpm_color(t_xpm_color *colors, char smb,
							size_t am);

SDL_Color				*get_point_from_xpm_texture(double x, double y,
							t_xpm_texture *txt);

int						read_map_textures(int fd,
							t_saved_xpm_texture **res, size_t am);

t_list					*read_map_surfaces(int fd,
							t_saved_xpm_texture **textures);

int						read_map(char *filename, t_scene *scene,
							t_xpm_texture ***textures);

int						save_map(t_xpm_texture **textures, t_scene *scene);

#endif
