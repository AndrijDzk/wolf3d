cmake_minimum_required(VERSION 3.9)
FUNCTION(PREPEND var prefix)
   SET(listVar "")
   FOREACH(f ${ARGN})
      LIST(APPEND listVar "${prefix}/${f}")
   ENDFOREACH(f)
   SET(${var} "${listVar}" PARENT_SCOPE)
ENDFUNCTION(PREPEND)

set(CMAKE_VERBOSE_MAKEFILE ON)

set(INC Includes)

set(COMMON common)

set(NAME1 wolf3d)
project(${NAME1} C)

set(NAME2 level_editor)
project(${NAME1} C)

set(TEST UnitTests)

set(LIBFT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Libs/libft)
set(LIBFT_BINARY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Libs/libft/CMakeFiles)

set(SDL2_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Libs/sdl2)
set(SDL2_BINARY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Libs/sdl2/CMakeFiles)

set(SDIR Srcs)

set(COMMON_SOURCES
	"t_vec3d_into_arr.c"
	"draw_point.c"
	"draw_line.c"
	"draw_polygon.c"
	"render_scene.c"
	"throw_current_image_on_screen.c"
	"print_sdl_error_and_return.c"
	"rotate_camera.c"
	"move_camera.c"
	"change_fov.c"
	"mouse.c"
	"keyboard.c"
	"get_screen_pixel_crd.c"
	"read_xpm_header.c"
	"read_xpm_colors.c"
	"recalculate_texture_part.c"
	"read_xpm_texture.c"
	"read_map_textures.c"
	"read_map_surfaces.c"
	"read_map.c"
	"save_map.c")

set(RASTERIZATION Rasterization)

set(RAST_SOURCES
	"get_vertexes.c"
	"get_vertex_projections.c"
	"project_out_of_sight_side.c"
	"project_segment.c"
	"get_texture_projection.c"
	"list_of_occupied.c"
	"add_new_occupied_segment.c"
	"draw_texture_line.c"
	"draw_texture_multithreaded_slave.c"
	"draw_texture_multithreaded.c"
	"draw_texture.c"
	"render_texture.c"
	"render_surface.c"
	"render_scene.c"
	"draw_xpm_image.c"
	"build_lines_from_vertexes.c"
	"get_left_and_right_borders.c"
	"approximate_texturing_data_along_line.c"
	"get_border_min_and_max_y.c"
	"fill_texturing_table.c"
	"calculate_texturing_data.c"
	"init_texture_crd.c"
	"perspective_divide.c"
	"get_point_from_texture.c")

PREPEND(RAST_SOURCES ${RASTERIZATION} ${RAST_SOURCES})
set(COMMON_SOURCES ${COMMON_SOURCES} ${RAST_SOURCES})

set(RAYCASTING Raycasting)

set(RAYCAST_SOURCES
	"get_ray_color.c"
	"renderer_slave.c"
	"render_scene_processor.c")

PREPEND(RAYCAST_SOURCES ${RAYCASTING} ${RAYCAST_SOURCES})
set(COMMON_SOURCES ${COMMON_SOURCES} ${RAYCAST_SOURCES})

set(BSP BSP)

set(BSP_SOURCES
	"divide_is_necessary.c"
	"proceed_node_surface.c"
	"divide_texture.c"
	"divide_surface.c"
	"divide_node.c"
	"check_new_nodes.c"
	"insert_into_tree.c"
	"insert_surface_into_tree.c"
	"build_bsp_tree.c"
	"clear_bsp_tree.c"
	"clear_bsp_stack.c"
	"free_bsp_tree.c"
	"proceed_bsp_node.c")

PREPEND(BSP_SOURCES ${BSP} ${BSP_SOURCES})
set(COMMON_SOURCES ${COMMON_SOURCES} ${BSP_SOURCES})

set(MATH Math)
set(MATH_SOURCES
	"check_limits.c"
	"get_rel_pos.c"
	"gj_elimination_correct_diagonal.c"
	"gj_eliminate_element.c"
	"matrix_inverse.c"
	"camera_matrix_inverse.c"
	"rotate_crd_system.c"
	"rotate_crd_system_relatively_to_world.c"
	"rotate.c"
	"matrix_math.c"
	"t_vec2d_into_t_vec3d.c"
	"t_vec3d_math.c"
	"t_vec3d_operations.c"
	"point_inside_quad.c")

PREPEND(MATH_SOURCES ${MATH} ${MATH_SOURCES})
set(COMMON_SOURCES ${COMMON_SOURCES} ${MATH_SOURCES})

set(INTERSECTIONS Intersections)
set(INTER_SOURCES
	"hor_and_vert_surfaces_intersection.c"
	"segment_quad_intersection.c"
	"intersections_2d.c"
	"surface_surface_intersection.c"
	"line_plane_intersection.c")

PREPEND(INTER_SOURCES ${INTERSECTIONS} ${INTER_SOURCES})
set(COMMON_SOURCES ${COMMON_SOURCES} ${INTER_SOURCES})

set(SOURCES1
	"main_loop.c"
	"init.c"
	"main.c")

set(SOURCES2
	"is_setting.c"
	"read_settings.c"
	"change_tmp_surface.c"
	"rotate_tmp_surface.c"
	"move_tmp_surface.c"
	"create_tmp_surface.c"
	"select_base_surface.c"
	"process_keydown_le.c"
	"main_loop.c"
	"init.c"
	"main.c")

set(TEST_SOURCES
	"translate_projections_into_screen_crd.c"
	"main.c")

PREPEND(COMMON_SOURCES ${COMMON} ${COMMON_SOURCES})
PREPEND(COMMON_SOURCES_REL ${SDIR} ${COMMON_SOURCES})
PREPEND(SOURCES1 ${NAME1} ${SOURCES1})
PREPEND(SOURCES_REL1 ${SDIR} ${SOURCES1})
PREPEND(SOURCES2 ${NAME2} ${SOURCES2})
PREPEND(SOURCES_REL2 ${SDIR} ${SOURCES2})
PREPEND(TEST_SOURCES_REL unit_tests ${TEST_SOURCES})

message("EXECUTABLE_OUTPUT_PATH - ${EXECUTABLE_OUTPUT_PATH}")
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR} CACHE PATH "Executable output dir" FORCE)
message("EXECUTABLE_OUTPUT_PATH - ${EXECUTABLE_OUTPUT_PATH}")

add_subdirectory(${SDL2_SOURCE_DIR} ${SDL2_BINARY_DIR})
link_libraries(SDL2-static)
include_directories(${SDL2_SOURCE_DIR}/include)

set(CMAKE_C_FLAGS "-Wall -Werror -Wextra")

add_executable(${NAME1} ${SOURCES_REL1} ${COMMON_SOURCES_REL})
target_include_directories(${NAME1} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/${INC}/${NAME1})
target_include_directories(${NAME1} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/${INC}/${COMMON})

add_executable(${NAME2} ${SOURCES_REL2} ${COMMON_SOURCES_REL})
target_include_directories(${NAME2} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/${INC}/${NAME2})
target_include_directories(${NAME2} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/${INC}/${COMMON})

add_executable(${TEST} ${TEST_SOURCES_REL} ${COMMON_SOURCES_REL})
target_include_directories(${TEST} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/${INC}/${NAME1})
target_include_directories(${TEST} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/${INC}/${NAME2})
target_include_directories(${TEST} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/${INC}/${COMMON})

add_subdirectory(${LIBFT_SOURCE_DIR} ${LIBFT_BINARY_DIR})
target_link_libraries(${NAME1} libft.a)
target_link_libraries(${NAME2} libft.a)
target_link_libraries(${TEST} libft.a)
include_directories(${LIBFT_INC})

target_link_libraries(${NAME1} "-framework OpenCL")
target_link_libraries(${NAME2} "-framework OpenCL")
