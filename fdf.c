/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoriyam <kmoriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 20:23:33 by kmoriyam          #+#    #+#             */
/*   Updated: 2025/01/24 22:19:05 by kmoriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilibx-linux/mlx.h"
#include "types.h"
#include "keycode.h"
#include "gnl/get_next_line.h"
#include "libft/libft.h"
#include <math.h>

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	if ((unsigned int)x >= WIN_WIDTH || (unsigned int)y >= WIN_HEIGHT)
		return ;
	*(unsigned int *)(data->addr +
		(y * data->line_length + x * (data->bits_per_pixel / 8))) = color;
}

unsigned int	hex_to_int(const char *hex_str)
{
	unsigned int	num;
	size_t			i;

	num = 0;
	i = 0;
	while (hex_str[i] && i < 8)
	{
		num = num << 4;
		if ('0' <= hex_str[i] && hex_str[i] <= '9')
			num = num + (hex_str[i] - '0');
		else if ('a' <= hex_str[i] && hex_str[i] <= 'z')
			num = num + (hex_str[i] - 'a') + 10;
		else if ('A' <= hex_str[i] && hex_str[i] <= 'Z')
			num = num + (hex_str[i] - 'A') + 10;
		i++;
	}
	return (num);
}

void	next_coordinate(t_coordinate *coordinate, t_line *line, int *error, int *error2)
{
	*error2 = *error * 2; // 次の移動方向を決めるために誤差値を2倍する
	if (*error2 > -coordinate->dy)
	{
		*error -= coordinate->dy; // 誤差を更新
		line->x0 += coordinate->sx; // 座標を更新
	}
	if (*error2 < coordinate->dx)
	{
		*error += coordinate->dx; // 誤差を更新
		line->y0 += coordinate->sy; // 座標を更新
	}
}

void	draw_line(t_data *data, t_line *line)
{
	t_coordinate	coordinate;
	int				error;
	int				error2;

	if ((line->x0 < 0 && line->x1 < 0) || (line->x0 >= WIN_WIDTH && line->x1 >= WIN_WIDTH) ||
		(line->y0 < 0 && line->y1 < 0) || (line->y0 >= WIN_HEIGHT && line->y1 >= WIN_HEIGHT))
		return ;
	coordinate.dx = abs(line->x1 - line->x0); // ｘ方向の距離
	coordinate.dy = abs(line->y1 - line->y0); // ｙ方向の距離
	if (line->x0 < line->x1)
		coordinate.sx = 1; // 右に進む
	else
		coordinate.sx = -1; // 左に進む
	if (line->y0 < line->y1)
		coordinate.sy = 1; // 下に進む
	else
		coordinate.sy = -1; // 上に進む
	error = coordinate.dx - coordinate.dy; // 誤差の初期値を設定
	while (1)
	{
		my_mlx_pixel_put(data, line->x0, line->y0, line->color);
		if (line->x0 == line->x1 && line->y0 == line->y1)
			break ;
		next_coordinate(&coordinate, line, &error, &error2);
	}
}

void	rotate_point(t_program *program, double *x, double *y, double *z)
{
	double	temp_x;
	double	temp_y;
	double	temp_z;

	temp_x = *x;
	temp_y = *x * 0 + *y * cos(program->angle_x) - *z * sin(program->angle_x);
	temp_z = *x * 0 + *y * sin(program->angle_x) + *z * cos(program->angle_x);
	*x = temp_x;
	*y = temp_y;
	*z = temp_z;
	temp_x = *x * cos(program->angle_y) + *y * 0 + *z * sin(program->angle_y);
	temp_y = *y;
	temp_z = -*x * sin(program->angle_y) + *y * 0 + *z * cos(program->angle_y);
	*x = temp_x;
	*y = temp_y;
	*z = temp_z;
	temp_x = *x * cos(program->angle_z) - *y * sin(program->angle_z) + *z * 0;
	temp_y = *x * sin(program->angle_z) + *y * cos(program->angle_z) + *z * 0;
	temp_z = *z;
	*x = temp_x;
	*y = temp_y;
	*z = temp_z;
}

void	draw_map(t_data *img, t_map *map, t_program *program)
{
	int	i;
	int	j;
	t_line	line;
	double	screen_x; // 3D座標を2D画面上に投影した位置
	double	screen_y; //
	double	x; // 3D空間での座標位置
	double	y; //
	double	z; //
	const double	height_factor = sqrt(2.0) / sqrt(3.0); // 高さの係数（等角投影のための調整値）

	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width[i])
		{
			// 等角投影のための計算
			x = (j - i) * program->cos; // x座標の計算
			y = (j + i) * program->sin; // y座標の計算
			z = map->z_value[i][j][0] * height_factor; // 高さ情報に係数を掛けて実際の3D座標に変換
			rotate_point(program, &x, &y, &z);
			// 3D座標を2D画面上の位置に変換
			// x座標 × 拡大率 + 画面中央 + xオフセット
			screen_x = (x * program->scale) + WIN_CENTER_X + program->offset_x;
			// y座標 × 拡大率 + 画面中央 + yオフセット
			screen_y = (y * program->scale) + WIN_CENTER_Y + program->offset_y;
			line.color = map->z_value[i][j][1];
			// my_mlx_pixel_put(img, line.x0, line.y0, line.color);
			if (j < map->width[i] - 1) // 横方向（右）への線を描画
			{
				line.x0 = screen_x; // 現在の点のx座標
				line.y0 = screen_y; // 現在の点のy座標
				x = ((j + 1) - i) * program->cos; // 次の点（右）のx座標
				y = ((j + 1) + i) * program->sin; // 次の点（右）のy座標
				z = map->z_value[i][j + 1][0] * height_factor; // 次の点の高さ
				rotate_point(program, &x, &y, &z);
				line.x1 = (x * program->scale) + WIN_CENTER_X + program->offset_x; // 右隣の点のx座標
				line.y1 = (y * program->scale) + WIN_CENTER_Y + program->offset_y; // 右隣の点のy座標
				draw_line(img, &line);
			}
			if (i < map->height - 1) // 縦方向（下）への線を描画
			{
				line.x0 = screen_x; // 現在の点のx座標
				line.y0 = screen_y; // 現在の点のy座標
				x = (j - (i + 1)) * program->cos; // 下の点のx座標
				y = (j + (i + 1)) * program->sin;  // 下の点のy座標
				z = map->z_value[i + 1][j][0] * height_factor; // 下の点の高さ
				rotate_point(program, &x, &y, &z);
				line.x1 = (x * program->scale) + WIN_CENTER_X + program->offset_x; // 下の点のx座標
				line.y1 = (y * program->scale) + WIN_CENTER_Y + program->offset_y; // 下の点のy座標
				draw_line(img, &line);
			}
			j++;
		}
		i++;
	}
}

int	count_word(const char *str, char delimeter)
{
	size_t	i;
	size_t	word_count;
	int		in_word;

	if (!str)
		return (0);
	i = 0;
	word_count = 0;
	in_word = 0;
	while (str[i])
	{
		if (str[i] != delimeter && str[i] != '\n')
		{
			if (in_word == 0)
			{
				in_word = 1;
				word_count++;
			}
		}
		else
			in_word = 0;
		i++;
	}
	return (word_count);
}

int	get_map_height(int fd)
{
	char	*line;
	int		i;

	i = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		i++;
		free(line);
	}
	close(fd);
	return (i);
}

t_map	*get_map_size(t_map *map, char *file, int fd)
{
	char	*line;
	int		i;

	map->height = get_map_height(fd);
	map->width = malloc(sizeof(int) * map->height);
	if (!map->width)
		return (NULL);
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		free(map->width);
		return (NULL);
	}
	i = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		map->width[i] = count_word(line, ' ');
		free(line);
		i++;
	}
	close(fd);
	return (map);
}

void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	free_map(t_map *map)
{
	int	i;
	int	j;
	
	if (!map)
		return ;
	i = -1;
	if (map->z_value)
	{
		while (++i < map->height)
		{
			if (map->z_value[i])
			{
				j = -1;
				while (++j < map->width[i] && map->z_value[i][j])
					free(map->z_value[i][j]);
				free(map->z_value[i]);
			}
		}
		free(map->z_value);
	}
	if (map->width)
		free(map->width);
	free(map);
}

void	all_free(t_program *program, t_map *map, char **array, char *line)
{
	if (program)
		free(program);
	if (map)
		free_map(map);
	if (array)
		free_array(array);
	if (line)
		free(line);
}

t_map	*init_map(t_map *map, char *file, int fd)
{
	map = (t_map *)malloc(sizeof(t_map));
	if (!map)
		return (NULL);
	map = get_map_size(map, file, fd);
	if (!map)
	{
		free(map);
		return (NULL);
	}
	return (map);
}

void	cleanup_mlx(t_program *program)
{
	if (!program)
		return ;
	if (program->img && program->img->img)
		mlx_destroy_image(program->vars->mlx, program->img->img);
	if (program->vars && program->vars->win)
		mlx_destroy_window(program->vars->mlx, program->vars->win);
	if (program->vars && program->vars->mlx)
	{
		mlx_destroy_display(program->vars->mlx);
		free(program->vars->mlx);
	}
}

void	clear_image(t_data *img)
{
	ft_memset(img->addr, 0, 1920 * 1080 * (img->bits_per_pixel / 8));
}

void	zoomzoom(t_program *program, int keycode)
{
	if (keycode == PLUS_KEY)
	{
		program->scale += 3;
		if (program->scale > 1000)
			program->scale = 1000;
	}
	else if (keycode == MINUS_KEY)
	{
		program->scale -= 3;
		if (program->scale < 2)
			program->scale = 2;
	}
}

void	wasd(t_program *program, int keycode)
{
	if (keycode == W_KEY)
		program->offset_y += 5;
	else if (keycode == S_KEY)
		program->offset_y -= 5;
	else if (keycode == D_KEY)
		program->offset_x -= 5;
	else if (keycode == A_KEY)
		program->offset_x += 5;
}

void	rotate_axis(t_program *program, int keycode)
{
	if (keycode == ARROW_RIGHT)
		program->angle_y -= 0.1;
	else if (keycode == ARROW_LEFT)
		program->angle_y += 0.1;
	else if (keycode == ARROW_DOWN)
		program->angle_x -= 0.1;
	else if (keycode == ARROW_UP)
		program->angle_x += 0.1;
	else if (keycode == X_KEY)
		program->angle_z -= 0.1;
	else if (keycode == Z_KEY)
		program->angle_z += 0.1;
}

int	 key_hook(int keycode, t_vars *vars)
{
	t_program	*program;

	program = vars->program;
	if (keycode == ESC_KEY)
	{
		cleanup_mlx(program);
		if (program && program->map)
			all_free(program, program->map, NULL, NULL);
		else
			all_free(program, NULL, NULL, NULL);
		exit(0);
	}
	else if (keycode == PLUS_KEY || keycode == MINUS_KEY)
		zoomzoom(program, keycode);
	else if (keycode == W_KEY || keycode == A_KEY || keycode == S_KEY || keycode == D_KEY)
		wasd(program, keycode);
	else if (keycode == ARROW_RIGHT || keycode == ARROW_LEFT || keycode == ARROW_DOWN ||
		keycode == ARROW_UP || keycode == X_KEY || keycode == Z_KEY)
		rotate_axis(program, keycode);
	clear_image(program->img);
	draw_map(program->img, program->map, program);
	mlx_put_image_to_window(program->vars->mlx, program->vars->win, program->img->img, 0, 0);
	mlx_string_put(vars->mlx, vars->win, 10, 10, 0x0000FFFF, vars->title);
	return (0);
}

int	close_window(t_vars *vars)
{
	t_program	*program;

	program = vars->program;
	cleanup_mlx(program);
	if (program && program->map)
			all_free(program, program->map, NULL, NULL);
	else
		all_free(program, NULL, NULL, NULL);
	exit(0);
}

t_program	*init_program(t_program	**program, t_vars *vars, t_data *img)
{
	*program = (t_program *)malloc(sizeof(t_program));
	if (!*program)
		return (NULL);
	(*program)->vars = vars;
	(*program)->img = img;
	(*program)->scale = 10;
	(*program)->offset_x = 0;
	(*program)->offset_y = 0;
	(*program)->angle_x = 0;
	(*program)->angle_y = 0;
	(*program)->angle_z = 0;
	(*program)->projected_x = 0.0;
	(*program)->projected_y = 0.0;
	(*program)->cos = cos(M_PI / 6);
	(*program)->sin = sin(M_PI / 6);
	return (*program);
}

int	validate_arg(char *file_name)
{
	int	len;

	len = ft_strlen(file_name);
	len--;
	if (file_name[len - 3] == '.' && file_name[len - 2] == 'f' &&
		file_name[len - 1] == 'd' && file_name[len] == 'f')
		return (1);
	else
		return (0);
}

int	ready_for_mlx(t_program *program, t_vars *vars, t_data *img)
{
	vars->mlx = mlx_init();
	if (!vars->mlx)
	{
		all_free(program, program->map, NULL, NULL);
		return (0);
	}
	vars->win = mlx_new_window(vars->mlx, 1920, 1080, vars->title);
	if (!vars->win)
	{
		all_free(program, program->map, NULL, NULL);
		cleanup_mlx(program);
		return (0);
	}
	img->img = mlx_new_image(vars->mlx, 1920, 1080);
	if (!img->img)
	{
		all_free(program, program->map, NULL, NULL);
		cleanup_mlx(program);
		return (0);
	}
	return (1);
}

int	main(int ac, char **av)
{
	t_program	*program;
	t_vars		vars;
	t_data		img;

	int			fd;
	char		*line;
	char		**array;
	char		**split_arr;
	t_map		*map;
	int			i;
	int			j;
	int			wc;

	if (ac > 2)
		return (1);
	if (!validate_arg(av[1]))
	{
		write(1, "Invalid Argument.\n", 18);
		return (1);
	}
	program = init_program(&program, &vars, &img);
	if (!program)
		return (1);
	vars.program = program;
	vars.title = av[1];
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
	{
		all_free(program, NULL, NULL, NULL);
		write(1, "Error\n", 6);
		return (1);
	}
	map = NULL;
	program->map = init_map(map, av[1], fd);
	if (!program->map)
	{
		all_free(program, NULL, NULL, NULL);
		write(1, "Error\n", 6);
		return (1);
	}
	program->map->z_value = malloc(sizeof(int **) * program->map->height);
	if (!program->map->z_value)
	{
		all_free(NULL, program->map, NULL, NULL);
		return (1);
	}
	i = 0;
	fd = open(av[1], O_RDONLY);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
		{
			printf("\n");
			break ;
		}
		wc = count_word(line, ' ');
		printf("\nline[%d] = %s", i, line);
		if (!ft_strchr(line, '\n'))
			printf("\n");
		array = ft_split(line, ' ');
		if (!array)
		{
			all_free(NULL, program->map, NULL, line);
			return (1);
		}
		program->map->z_value[i] = malloc(sizeof(int *) * program->map->width[i]);
		if (!program->map->z_value[i])
		{
			all_free(NULL, program->map, array, line);
			return (1);
		}
		j = 0;
		while (j < wc)
		{
			program->map->z_value[i][j] = malloc(sizeof(int) * 2);
			if (!program->map->z_value[i][j])
			{
				all_free(NULL, program->map, array, line);
				return (1);
			}
			if (array[j])
			{
				if (!ft_strchr(array[j], ','))
				{
					program->map->z_value[i][j][0] = ft_atoi(array[j]); 
					program->map->z_value[i][j][1] = 0x0000FFFF;
				}
				else
				{
					split_arr = ft_split(array[j], ',');
					if (!split_arr)
					{
						all_free(NULL, program->map, NULL, array[j]);
						return (1);
					}
					program->map->z_value[i][j][0] = ft_atoi(split_arr[0]);
					if (ft_strlen(split_arr[1]) > 2 && split_arr[1][0] == '0' &&
						(split_arr[1][1] == 'x' || split_arr[1][1] == 'X'))
						program->map->z_value[i][j][1] = hex_to_int(split_arr[1] + 2);
					else
						program->map->z_value[i][j][1] = 0x00FFFF00;
					all_free(NULL, NULL, split_arr, NULL);
				}
				printf("z_value[%d][%d] = h:%d, c: %d\n", i, j, program->map->z_value[i][j][0], program->map->z_value[i][j][1]);
			}
			j++;
		}
		all_free(NULL, NULL, array, line);
		i++;
	}
	close(fd);

	if (!ready_for_mlx(program, &vars, &img))
	{
		write(1, "Error\n", 6);
		return (1);
	}
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	draw_map(&img, program->map, program);
	mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);
	mlx_string_put(vars.mlx, vars.win, 10, 10, 0x0000FFFF, vars.title);
	mlx_hook(vars.win, 2, 1L<<0, key_hook, &vars);
	mlx_hook(vars.win, 17, 0, close_window, &vars);
	mlx_loop(vars.mlx);
	cleanup_mlx(program);
	all_free(program, program->map, NULL, NULL);
}
