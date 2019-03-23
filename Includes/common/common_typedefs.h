/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common_typedefs.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/11 15:04:31 by adzikovs          #+#    #+#             */
/*   Updated: 2018/11/24 11:28:39 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMON_TYPEDEFS_H
# define COMMON_TYPEDEFS_H

# include "common_defines.h"

# include "SDL.h"

# include "libft.h"

enum					e_cont_type {Cont_S_Arr, Cont_H_Arr, Cont_t_list};

enum					e_input_action {eiaNone, eiaMouseMove, eiaEscape,
	eiaMoveCameraForward, eiaMoveCameraBackward,
	eiaMoveCameraLeft, eiaMoveCameraRight,
	eiaMoveCameraUp, eiaMoveCameraDown,
	eiaRotCameraLeft, eiaRotCameraRight,
	eiaRotCameraUp, eiaRotCameraDown,
	eiaRotCameraClockwise, eiaRotCameraCounterClockwise,
	eiaIncreaseFOV, eiaDecreaseFOV};

enum					e_visual_type {evtColor, evtTexture};

typedef struct			s_texturing_data
{
	double				bounds[2];
	double				x_z[2];
	double				y_z[2];
	double				one_z[2];
}						t_texturing_data;

typedef struct			s_texturing_table
{
	int					y_start;
	int					y_end;
	t_texturing_data	*rows;
}						t_texturing_table;

typedef struct			s_xpm_color
{
	char				smb;
	SDL_Color			color;
}						t_xpm_color;

typedef struct			s_xpm_header
{
	int					w;
	int					h;
	size_t				colors;
	int					chars_per_pixel;
}						t_xpm_header;

typedef struct			s_xpm_texture
{
	t_xpm_header		header;
	t_xpm_color			*colors;
	double				x[2];
	double				y[2];
	char				*data;
}						t_xpm_texture;

typedef struct			s_saved_xpm_texture
{
	t_xpm_texture		texture;
	char				*old_data_ptr;
}						t_saved_xpm_texture;

typedef struct			s_vec3d
{
	double				x;
	double				y;
	double				z;
}						t_vec3d;

typedef struct			s_vec2d
{
	double				x;
	double				y;
}						t_vec2d;

/*
** ax + by = c
** x E [x[0],x[1]]
** y E [y[0],y[1]]
*/

typedef struct			s_2d_segment
{
	double				a;
	double				b;
	double				c;
	double				x[2];
	double				y[2];
}						t_2d_segment;

typedef struct			s_textured_2d_segment
{
	t_2d_segment		segment;
	t_texturing_data	data;
}						t_textured_2d_segment;

typedef struct			s_ray
{
	t_vec3d				pos;
	t_vec3d				dir;
}						t_ray;

typedef struct			s_plane
{
	t_vec3d				norm;
	t_vec3d				pos;
}						t_plane;

typedef struct			s_surface
{
	t_plane				plane;
	double				length;
	double				height;
	char				inf;
	enum e_visual_type	visual_type;
	union
	{
		SDL_Color		color;
		t_xpm_texture	texture;
	}					visual;
}						t_surface;

typedef struct			s_bsp_node
{
	t_surface			*surface;
	t_surface			*initial_surface;
	struct s_bsp_node	*front;
	struct s_bsp_node	*rear;
}						t_bsp_node;

typedef struct			s_camera
{
	double				m[4][4];
	int					focal_length;
	double				x_scale;
	double				y_scale;
	int					w;
	int					h;
}						t_camera;

typedef struct			s_scene
{
	enum e_cont_type	cont_type;
	union
	{
		t_surface		s_surfaces[2];
		t_surface		*h_surfaces;
		t_list			*l_surfaces;
	}					container;
	unsigned			surfaces_am;
	t_bsp_node			*bsp_tree;
}						t_scene;

typedef struct			s_window
{
	SDL_Window			*window;
	SDL_Surface			*surface;
	t_list				*screen_data[MAX_WINDOW_HEIGHT];
}						t_window;

typedef struct			s_sdl
{
	SDL_DisplayMode		display_mode;
	t_window			window;
}						t_sdl;

typedef struct			s_renderer_slave_param
{
	t_sdl				*sdl;
	t_scene				*scene;
	t_camera			*camera;
	int					y_start;
	int					y_end;
	int					x_start;
	int					x_end;
}						t_renderer_slave_param;

typedef t_textured_2d_segment	*t_borders_table[2][5];

typedef struct			s_drt_slave_param
{
	int					y_start;
	int					y_end;
	t_sdl				*sdl;
	t_borders_table		*borders;
	t_xpm_texture		*txt;
}						t_drt_slave_param;

typedef int				(*t_keydown_handler)(t_sdl *, t_scene *, t_camera *,
						enum e_input_action);

#endif
