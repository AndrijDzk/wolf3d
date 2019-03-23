COMMON = common

NAME1 = wolf3d

NAME2 = level_editor

CC = gcc
CFLAGS = -Wall -Werror -Wextra
CLFLAGS =	-lobjc\
			-liconv\
			-Wl,-framework,OpenGL\
			-Wl,-framework,ForceFeedback\
			-Wl,-framework,Cocoa\
			-Wl,-framework,Carbon\
			-Wl,-framework,IOKit\
			-Wl,-framework,CoreAudio\
			-Wl,-framework,AudioToolbox\
			-Wl,-framework,AudioUnit\
			-Wl,-framework,CoreVideo\
			-Wl,-framework,Metal

INC = Includes

SDIR = Srcs

COMMON_SRCS = \
		recalculate_texture_part.c\
		t_vec3d_into_arr.c\
		throw_current_image_on_screen.c\
		print_sdl_error_and_return.c\
		render_scene.c\
		rotate_camera.c\
		move_camera.c\
		mouse.c\
		keyboard.c\
		draw_point.c\
		draw_line.c\
		draw_polygon.c\
		get_screen_pixel_crd.c\
		read_xpm_header.c\
		read_xpm_colors.c\
		read_xpm_texture.c\
		read_map_textures.c\
		read_map_surfaces.c\
		read_map.c\
		save_map.c\
		change_fov.c\

RAST = Rasterization

RAST_SRCS = \
		get_vertexes.c\
		get_vertex_projections.c\
		project_out_of_sight_side.c\
		project_segment.c\
		get_texture_projection.c\
		add_new_occupied_segment.c\
		list_of_occupied.c\
		draw_texture_line.c\
		draw_texture_multithreaded_slave.c\
		draw_texture_multithreaded.c\
		draw_texture.c\
		render_texture.c\
		render_surface.c\
		render_scene.c\
		draw_xpm_image.c\
		build_lines_from_vertexes.c\
		get_left_and_right_borders.c\
		approximate_texturing_data_along_line.c\
		get_border_min_and_max_y.c\
		fill_texturing_table.c\
		calculate_texturing_data.c\
		init_texture_crd.c\
		perspective_divide.c\
		get_point_from_texture.c\

RAST_SRCS_R = $(RAST_SRCS:%.c=$(RAST)/%.c)

COMMON_SRCS += $(RAST_SRCS_R)

RAYCAST = Raycasting

RAYCAST_SRCS = \
		get_ray_color.c\
		renderer_slave.c\
		render_scene_processor.c\

RAYCAST_SRCS_R = $(RAYCAST_SRCS:%.c=$(RAYCAST)/%.c)

COMMON_SRCS += $(RAYCAST_SRCS_R)

BSP = BSP

BSP_SRCS = \
		proceed_node_surface.c\
		divide_texture.c\
		divide_surface.c\
		divide_node.c\
		check_new_nodes.c\
		insert_into_tree.c\
		insert_surface_into_tree.c\
		divide_is_necessary.c\
		build_bsp_tree.c\
		clear_bsp_tree.c\
		clear_bsp_stack.c\
		free_bsp_tree.c\
		proceed_bsp_node.c\

BSP_SRCS_R = $(BSP_SRCS:%.c=$(BSP)/%.c)

COMMON_SRCS += $(BSP_SRCS_R)

MATH = Math

MATH_SRCS = \
		check_limits.c\
		get_rel_pos.c\
		gj_elimination_correct_diagonal.c\
		gj_eliminate_element.c\
		matrix_inverse.c\
		camera_matrix_inverse.c\
		rotate_crd_system.c\
		rotate_crd_system_relatively_to_world.c\
		rotate.c\
		matrix_math.c\
		t_vec2d_into_t_vec3d.c\
		t_vec3d_math.c\
		t_vec3d_operations.c\
		point_inside_quad.c\

MATH_SRCS_R = $(MATH_SRCS:%.c=$(MATH)/%.c)

COMMON_SRCS += $(MATH_SRCS_R)

INTERSECTIONS = Intersections

INTER_SRCS = \
		hor_and_vert_surfaces_intersection.c\
		segment_quad_intersection.c\
		intersections_2d.c\
		surface_surface_intersection.c\
		line_plane_intersection.c\

INTER_SRCS_R = $(INTER_SRCS:%.c=$(INTERSECTIONS)/%.c)

COMMON_SRCS += $(INTER_SRCS_R)

COMMON_SRCS_R = $(COMMON_SRCS:%.c=$(SDIR)/$(COMMON)/%.c)

SRCS1 = \
		main_loop.c\
		init.c\
		main.c\

SRCS1_R = $(SRCS1:%.c=$(SDIR)/$(NAME1)/%.c)

SRCS2 = \
		is_setting.c\
		read_settings.c\
		change_tmp_surface.c\
		rotate_tmp_surface.c\
		move_tmp_surface.c\
		create_tmp_surface.c\
		select_base_surface.c\
		process_keydown_le.c\
		main_loop.c\
		init.c\
		main.c\

SRCS2_R = $(SRCS2:%.c=$(SDIR)/$(NAME2)/%.c)

COMMON_HEADERS = \
					bsp.h\
					camera.h\
					common.h\
					common_defines.h\
					common_typedefs.h\
					intersections.h\
					math_3d.h\
					matrix_math.h\
					rasterization.h\
					return_codes.h\
					t_vec3d_math.h\

COMMON_HEADERS_R = $(COMMON_HEADERS:%.h=Includes/common/%.h)

HEADERS1 = \
			return_codes.h\
			wolf3d_defines.h\
			wolf3d.h

HEADERS1_R = $(HEADERS1:%.h=$(INC)/$(NAME1)/%.h)

HEADERS2 = \
			level_editor.h\
			level_editor_defines.h\
			level_editor_typedefs.h\

HEADERS2_R = $(HEADERS2:%.h=$(INC)/$(NAME2)/%.h)

ODIR = Objects

COMMON_OBJ = $(COMMON_SRCS:%.c=%.o)
COMMON_OBJ_R = $(COMMON_OBJ:%.o=$(ODIR)/$(COMMON)/%.o)

OBJ1 = $(SRCS1:%.c=%.o)
OBJ1_R = $(OBJ1:%.o=$(ODIR)/$(NAME1)/%.o)

OBJ2 = $(SRCS2:%.c=%.o)
OBJ2_R = $(OBJ2:%.o=$(ODIR)/$(NAME2)/%.o)

all : $(ODIR)/ $(NAME1) $(NAME2)

$(NAME1) : $(ODIR)/$(COMMON)/ $(ODIR)/$(NAME1)/ $(OBJ1_R) $(COMMON_OBJ_R)
	make -C Libs/libft
	make -C Libs/sdl2
	$(CC) $(CFLAGS) -o $(NAME1) $(COMMON_OBJ_R) $(OBJ1_R) Libs/libft/libft.a Libs/sdl2/build/.libs/libSDL2.a $(CLFLAGS)

$(NAME2) : $(ODIR)/$(COMMON)/ $(ODIR)/$(NAME2)/ $(OBJ2_R) $(COMMON_OBJ_R)
	make -C Libs/libft
	make -C Libs/sdl2
	$(CC) $(CFLAGS) -o $(NAME2) $(COMMON_OBJ_R) $(OBJ2_R) Libs/libft/libft.a Libs/sdl2/build/.libs/libSDL2.a $(CLFLAGS)

find_globals : $(ODIR)/$(COMMON)/ $(ODIR)/$(NAME1)/ $(ODIR)/$(NAME2)/ $(OBJ1_R) $(OBJ2_R) $(COMMON_OBJ_R)
	make -C Libs/libft
	ar rc test.a $(COMMON_OBJ_R) $(OBJ1_R) $(OBJ2_R) Libs/libft/libft.a
	nm test.a | grep -E "( D )|( d )"

.PHONY: clean1 fclean1 re1 clean2 fclean2 re2 clean fclean re

clean1 :
	rm -f $(OBJ1_R)

fclean1 : clean1
	rm -f $(NAME1)

re1 : fclean1 $(NAME1)

clean2 :
	rm -f $(OBJ2_R)

fclean2 : clean2
	rm -f $(NAME2)

re2 : fclean2 $(NAME2)

clean : clean1 clean2

fclean : clean
	rm -f $(NAME1) $(NAME2)

re : fclean all

norm:
	make norm -C Libs/libft
	norminette $(COMMON_HEADERS_R) $() $(HEADERS1_R) $(SRCS1_R)

add:
	make add -C Libs/libft
	git add $(SRCS1_R) $(HEADERS1_R)\
		$(SRCS2_R) $(HEADERS2_R)\
		$(COMMON_SRCS_R) $(COMMON_HEADERS_R) .gitignore Makefile CMakeLists.txt author

test1: $(NAME1)
	./$(NAME1)

$(ODIR)/ :
	mkdir -p $@

$(ODIR)/$(COMMON)/ :
	mkdir -p $@
	mkdir -p $@/$(BSP)
	mkdir -p $@/$(INTERSECTIONS)
	mkdir -p $@/$(MATH)
	mkdir -p $@/$(RAST)
	mkdir -p $@/$(RAYCAST)

$(ODIR)/$(NAME1)/ :
	mkdir -p $@

$(ODIR)/$(NAME2)/ :
	mkdir -p $@

$(ODIR)/$(COMMON)/%.o : $(SDIR)/$(COMMON)/%.c $(COMMON_HEADERS_R)
	$(CC) $(CFLAGS) -c $< -o $@ -I Libs/libft/Includes -I $(INC)/$(COMMON) -I Libs/sdl2/include

$(ODIR)/$(NAME1)/%.o : $(SDIR)/$(NAME1)/%.c $(COMMON_HEADERS_R) $(HEADERS1_R)
	$(CC) $(CFLAGS) -c $< -o $@ -I Libs/libft/Includes -I $(INC)/$(NAME1) -I $(INC)/$(COMMON) -I Libs/sdl2/include

$(ODIR)/$(NAME2)/%.o : $(SDIR)/$(NAME2)/%.c $(COMMON_HEADERS_R) $(HEADERS2_R)
	$(CC) $(CFLAGS) -c $< -o $@ -I Libs/libft/Includes -I $(INC)/$(NAME2) -I $(INC)/$(COMMON) -I Libs/sdl2/include
