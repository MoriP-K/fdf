/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoriyam <kmoriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 20:17:18 by kmoriyam          #+#    #+#             */
/*   Updated: 2025/02/02 14:04:59 by kmoriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include "minilibx-linux/mlx.h"
# include "gnl/get_next_line.h"
# include "libft/libft.h"
# include "types.h"
# include <stdlib.h>
# include <math.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>

void				my_mlx_pixel_put(t_data *data, int x, int y, int color);
int					validate_arg(int ac, char *file_name);
void				free_map(t_map *map);
void				throwing_error(int error_no);
void				all_free(t_all *all, int flag, int errorno);
void				set_default_value(t_program *program);
t_program			*init_program(t_vars *vars, t_data *img, t_map *map);
t_data				*init_data(void);
t_vars				*init_vars(t_program *program, char *file);
t_str				*init_str(void);
int					get_map_height(int fd);
int					count_word(const char *str, char delimeter);
int					clean_up_width(int *check);
int					get_map_width(int fd, char *file, int height, int **check);
t_map				*get_map_size(t_all *all, t_map *map);
void				init_map_data(t_map *map);
t_map				*init_map(t_all *all);
t_line				*init_line(void);
t_point				*init_point(void);
void				init_all_structure(t_all **all, char *file);
unsigned int		hex_to_int(const char *hex_str);
void				free_array(char **array);
int					assign_data_and_color(int *z_value, char *arr);
int					get_data_and_color(int **z_value, char **arr, int *width);
int					get_map_data(t_map *map, char **arr, int *height);
void				read_map_data(t_all *all);
void				clean_up_mlx(t_all *all);
int					ready_for_mlx(t_all *all);
void				next_point(t_point *point, t_line *line,
						int *error, int *error2);
int					is_draw_window(int x0, int x1, int y0, int y1);
void				draw_line(t_all *all, t_line *line);
void				rotate_xyz(t_program *program,
						double *x, double *y, double *z);
void				set_point_xyz(t_all *all, t_map *map, int i, int j);
void				convert_to_isometric(t_point *point, t_program *program);
void				convert_to_isometric_next(t_point *point,
						t_program *program, t_line *line);
void				project_point(t_all *all, t_program *program,
						t_line *line, int flag);
void				set_draw_point_xy(t_line *line, t_program *program);
void				draw_map(t_all *all, t_map *map,
						t_program *program, t_line *line);
void				clear_image(t_data *img);
int					move_fdf(int keycode, t_all *all);
void				reset_position(t_program *program);
void				rotate_axis(t_program *program, int keycode);
void				wasd(t_program *program, int keycode);
void				zoomzoom(t_program *program, int keycode);
void				put_instructions_to_window(t_vars *vars);
int					close_window(t_all *all);
void				start_fdf(t_all *all);

#endif