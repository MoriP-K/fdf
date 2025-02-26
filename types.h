/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoriyam <kmoriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 15:04:39 by kmoriyam          #+#    #+#             */
/*   Updated: 2025/02/01 22:41:04 by kmoriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H
# include "keycode.h"
# define WIN_H 1080
# define WIN_W 1920
# define WIN_CENTER_Y 540
# define WIN_CENTER_X 960
# define NONE 0
# define INVALID_ARG 1
# define PROCESSING 2
# define ON_KEY_DOWN 2
# define ON_DESTROY 17

typedef struct s_program	t_program;
typedef struct s_vars		t_vars;
typedef struct s_data		t_data;
typedef struct s_map		t_map;
typedef struct s_line		t_line;
typedef struct s_str		t_str;
typedef struct s_all		t_all;
typedef struct s_point		t_point;

typedef struct s_all
{
	t_program	*program;
	t_vars		*vars;
	t_data		*img;
	t_map		*map;
	t_str		*str;
	t_line		*line;
	t_point		*point;
	int			fd;
	char		*file;
}				t_all;

typedef struct s_program
{
	t_vars		*vars;
	t_data		*img;
	t_map		*map;
	int			word_count;
	int			scale;
	int			offset_x;
	int			offset_y;
	double		angle_x;
	double		angle_y;
	double		angle_z;
	double		screen_x;
	double		screen_y;
	double		cos;
	double		sin;
}				t_program;

typedef struct s_vars
{
	void		*mlx;
	void		*win;
	t_program	*program;
	char		*title;
}				t_vars;

typedef struct s_data
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_data;

typedef struct s_map
{
	int			*check_width;
	double		width;
	double		height;
	int			***z_value;
}				t_map;

typedef struct s_line
{
	int			x0;
	int			y0;
	int			x1;
	int			y1;
	int			color;
}				t_line;

typedef struct s_point
{
	double		x;
	double		y;
	double		z;
	int			dx;
	int			dy;
	int			sx;
	int			sy;
	double		tmp_x;
	double		tmp_y;
}				t_point;

typedef struct s_str
{
	char		*line;
	char		**arr;
}				t_str;

#endif
