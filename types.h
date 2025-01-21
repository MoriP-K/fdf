/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoriyam <kmoriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 15:04:39 by kmoriyam          #+#    #+#             */
/*   Updated: 2025/01/21 22:08:29 by kmoriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H
# include <stdlib.h>
# include <math.h>
# define MY_PI 3.141592653589793238462643
# define WIN_HEIGHT 1080
# define WIN_WIDTH 1920
# define WIN_CENTER_Y 960
# define WIN_CENTER_X 540

typedef struct s_program t_program;
typedef struct s_vars t_vars;
typedef struct s_data t_data;
typedef struct s_map t_map;
typedef struct s_line t_line;

typedef struct	s_program
{
	t_vars		*vars;
	t_data		*img;
	t_map		*map;
	int			scale;
	int			offset_x;
	int			offset_y;
	double		angle_x;
	double		angle_y;
	double		angle_z;
	double		rotate_x;
	double		rotate_y;
	double		rotate_z;
	double		projected_x;
	double		projected_y;
	double		cos;
	double		sin;
}				t_program;

typedef struct	s_vars
{
	void		*mlx;
	void		*win;
	t_program	*program;
	char		*title;
}				t_vars;

typedef struct	s_data
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_data;

typedef struct	s_map
{
	int			*width;
	int			height;
	int			***z_value;
}				t_map;

typedef struct	s_line
{
	int			x0;
	int			y0;
	int			x1;
	int			y1;
	int			color;
}				t_line;

typedef struct	s_coordinate
{
	int			dx;
	int			dy;
	int			sx;
	int			sy;
}				t_coordinate;

#endif
