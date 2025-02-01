/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoriyam <kmoriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 15:04:54 by kmoriyam          #+#    #+#             */
/*   Updated: 2025/02/01 23:29:40 by kmoriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
// {
// 	if ((unsigned int)x >= WIN_W || (unsigned int)y >= WIN_H)
// 		return ;
// 	*(unsigned int *)(data->addr + (y * data->line_length
// 		+ x * (data->bits_per_pixel / 8))) = color;
// }

int	validate_arg(int ac, char *file_name)
{
	int	len;

	if (ac != 2)
		return (0);
	len = ft_strlen(file_name);
	len--;
	if (file_name[len - 3] != '.' || file_name[len - 2] != 'f'
		|| file_name[len - 1] != 'd' || file_name[len] != 'f')
		return (0);
	return (1);
}

// void	free_map(t_map *map)
// {
// 	int	i;
// 	int	j;

// 	if (!map)
// 		return ;
// 	i = 0;
// 	if (map->z_value)
// 	{
// 		while (i < map->height)
// 		{
// 			if (map->z_value[i])
// 			{
// 				j = 0;
// 				while (j < map->width && map->z_value[i][j])
// 				{
// 					free(map->z_value[i][j]);
// 					j++;
// 				}
// 				free(map->z_value[i]);
// 			}
// 			i++;
// 		}
// 		free(map->z_value);
// 	}
// 	free(map);
// }

// void	throwing_error(int error_no)
// {
// 	if (error_no == INVALID_ARG)
// 		write(2, "Invalid Argument.\n", 18);
// 	else if (error_no == PROCESSING)
// 		write(1, "Error\n", 6);
// 	exit(EXIT_FAILURE);
// }

// void	all_free(t_all *all, int flag, int errorno)
// {
// 	if (!all)
// 		return ;
// 	if (all->program)
// 		free(all->program);
// 	if (all->img)
// 		free(all->img);
// 	if (all->vars)
// 		free(all->vars);
// 	if (all->str)
// 	{
// 		if (all->str->line)
// 			free(all->str->line);
// 		free(all->str);
// 	}
// 	if (all->map)
// 		free_map(all->map);
// 	if (all->line)
// 		free(all->line);
// 	if (all->point)
// 		free(all->point);
// 	if (all)
// 		free(all);
// 	if (flag)
// 		throwing_error(errorno);
// }

// void	set_default_value(t_program *program)
// {
// 	program->scale = program->map->height;
// 	program->offset_x = 0;
// 	program->offset_y = 0;
// 	program->angle_x = 0;
// 	program->angle_y = 0;
// 	program->angle_z = 0;
// 	program->screen_x = 0.0;
// 	program->screen_y = 0.0;
// 	program->cos = cos(M_PI / 6);
// 	program->sin = sin(M_PI / 6);
// }

// t_program	*init_program(t_vars *vars, t_data *img, t_map *map)
// {
// 	t_program	*program;

// 	program = (t_program *)malloc(sizeof(t_program));
// 	if (!program)
// 		return (NULL);
// 	program->vars = vars;
// 	program->img = img;
// 	program->map = map;
// 	set_default_value(program);
// 	return (program);
// }

// t_data	*init_data(void)
// {
// 	t_data	*data;

// 	data = (t_data *)malloc(sizeof(t_data));
// 	if (!data)
// 		return (NULL);
// 	return (data);
// }

// t_vars	*init_vars(t_program *program, char *file)
// {
// 	t_vars	*vars;

// 	vars = (t_vars *)malloc(sizeof(t_vars));
// 	if (!vars)
// 		return (NULL);
// 	vars->program = program;
// 	vars->title = file;
// 	return (vars);
// }

// t_str	*init_str(void)
// {
// 	t_str	*str;

// 	str = (t_str *)malloc(sizeof(t_str));
// 	if (!str)
// 		return (NULL);
// 	str->arr = NULL;
// 	str->line = NULL;
// 	return (str);
// }

// int	get_map_height(int fd)
// {
// 	int			height;
// 	char		*line;

// 	height = 0;
// 	while (1)
// 	{
// 		line = get_next_line(fd);
// 		if (!line)
// 			break ;
// 		free(line);
// 		height++;
// 	}
// 	close(fd);
// 	return (height);
// }

// int	count_word(const char *str, char delimeter)
// {
// 	size_t	i;
// 	size_t	word_count;
// 	int		in_word;

// 	if (!str)
// 		return (0);
// 	i = 0;
// 	word_count = 0;
// 	in_word = 0;
// 	while (str[i])
// 	{
// 		if (str[i] != delimeter && str[i] != '\n')
// 		{
// 			if (in_word == 0)
// 			{
// 				in_word = 1;
// 				word_count++;
// 			}
// 		}
// 		else
// 			in_word = 0;
// 		i++;
// 	}
// 	return (word_count);
// }

// int	clean_up_width(int *check)
// {
// 	int	width;

// 	width = check[0];
// 	free(check);
// 	return (width);
// }

// int	get_map_width(int fd, char *file, int height, int **check)
// {
// 	char	*line;
// 	int		i;

// 	fd = open(file, O_RDONLY);
// 	*check = malloc(sizeof(int) * height);
// 	if (fd == -1 || !*check)
// 		return (-1);
// 	i = 0;
// 	while (1)
// 	{
// 		line = get_next_line(fd);
// 		if (!line)
// 			break ;
// 		(*check)[i] = count_word(line, ' ');
// 		free(line);
// 		if (i > 0 && (*check)[i] >= 2 && (*check)[i - 1] != (*check)[i])
// 		{
// 			free(*check);
// 			close(fd);
// 			return (-1);
// 		}
// 		i++;
// 	}
// 	close(fd);
// 	return (clean_up_width(*check));
// }

// t_map	*get_map_size(t_all *all, t_map *map)
// {
// 	map->height = get_map_height(all->fd);
// 	map->width = get_map_width(all->fd, all->file, map->height,
// 			&map->check_width);
// 	if (map->width <= 1 || map->height <= 1)
// 		return (NULL);
// 	return (map);
// }

// t_map	*init_map(t_all *all)
// {
// 	t_map	*map;

// 	map = (t_map *)malloc(sizeof(t_map));
// 	if (!map)
// 		return (NULL);
// 	if (!get_map_size(all, map))
// 	{
// 		free(map);
// 		all_free(all, 1, INVALID_ARG);
// 	}
// 	map->z_value = malloc(sizeof(int **) * map->height);
// 	if (!map->z_value)
// 	{
// 		free(map);
// 		all_free(all, 0, NONE);
// 		return (NULL);
// 	}
// 	return (map);
// }

// t_line	*init_line(void)
// {
// 	t_line	*line;

// 	line = (t_line *)malloc(sizeof(t_line));
// 	if (!line)
// 		return (NULL);
// 	line->x0 = 0;
// 	line->x1 = 0;
// 	line->y0 = 0;
// 	line->y1 = 0;
// 	line->color = 0;
// 	return (line);
// }

// t_point	*init_point(void)
// {
// 	t_point	*point;

// 	point = (t_point *)malloc(sizeof(t_point));
// 	if (!point)
// 		return (NULL);
// 	point->x = 0;
// 	point->y = 0;
// 	point->z = 0;
// 	point->dx = 0;
// 	point->dy = 0;
// 	point->sx = 0;
// 	point->sy = 0;
// 	point->tmp_x = 0;
// 	point->tmp_y = 0;
// 	return (point);
// }

void	init_all_structure(t_all **all, char *file)
{
	*all = (t_all *)malloc(sizeof(t_all));
	if (!*all)
		exit(EXIT_FAILURE);
	ft_memset(*all, 0, sizeof(t_all));
	(*all)->fd = open(file, O_RDONLY);
	if ((*all)->fd == -1)
		exit (EXIT_FAILURE);
	(*all)->file = file;
	(*all)->img = init_data();
	(*all)->map = init_map(*all);
	(*all)->vars = init_vars((*all)->program, file);
	(*all)->program = init_program((*all)->vars, (*all)->img, (*all)->map);
	(*all)->vars->program = (*all)->program;
	(*all)->str = init_str();
	(*all)->line = init_line();
	(*all)->point = init_point();
	(*all)->fd = open(file, O_RDONLY);
	if (!(*all)->program || !(*all)->img || !(*all)->vars || !(*all)->str
		|| !(*all)->map || !(*all)->line || !(*all)->point || (*all)->fd == -1)
		all_free(*all, 1, PROCESSING);
}

// unsigned int	hex_to_int(const char *hex_str)
// {
// 	unsigned int	num;
// 	size_t			i;

// 	num = 0;
// 	i = 2;
// 	while (hex_str[i] && i < 10)
// 	{
// 		num = num * 16;
// 		if ('0' <= hex_str[i] && hex_str[i] <= '9')
// 			num = num + (hex_str[i] - '0');
// 		else if ('a' <= hex_str[i] && hex_str[i] <= 'z')
// 			num = num + (hex_str[i] - 'a') + 10;
// 		else if ('A' <= hex_str[i] && hex_str[i] <= 'Z')
// 			num = num + (hex_str[i] - 'A') + 10;
// 		i++;
// 	}
// 	return (num);
// }

// void	free_array(char **array)
// {
// 	int	i;

// 	i = 0;
// 	while (array[i])
// 	{
// 		free(array[i]);
// 		i++;
// 	}
// 	free(array);
// }

// int	assign_data_and_color(int *z_value, char *arr)
// {
// 	char	**split_arr;

// 	if (!ft_strchr(arr, ','))
// 	{
// 		z_value[0] = ft_atoi(arr);
// 		z_value[1] = hex_to_int("0x0000FFFF");
// 		return (1);
// 	}
// 	split_arr = ft_split(arr, ',');
// 	if (!split_arr)
// 		return (0);
// 	z_value[0] = ft_atoi(split_arr[0]);
// 	if (ft_strlen(split_arr[1]) > 2 && split_arr[1][0] == '0' &&
// 		(split_arr[1][1] == 'x' || split_arr[1][1] == 'X'))
// 	{
// 		z_value[1] = hex_to_int(split_arr[1]);
// 		free_array(split_arr);
// 		return (1);
// 	}
// 	free(split_arr);
// 	return (0);
// }

// int	get_data_and_color(int **z_value, char **arr, int *width)
// {
// 	z_value[*width] = malloc(sizeof(int) * 2);
// 	if (!z_value)
// 		return (0);
// 	if (arr[*width])
// 	{
// 		if (!assign_data_and_color(z_value[*width], arr[*width]))
// 			return (0);
// 	}
// 	return (1);
// }

// int	get_map_data(t_map *map, char **arr, int *height)
// {
// 	int	j;

// 	map->z_value[*height] = malloc(sizeof(int *) * map->width);
// 	if (!map->z_value[*height])
// 		return (0);
// 	j = 0;
// 	while (j < map->width)
// 	{
// 		if (!get_data_and_color(map->z_value[*height], arr, &j))
// 			return (0);
// 		j++;
// 	}
// 	return (1);
// }

void	read_map_data(t_all *all)
{
	int		i;

	i = 0;
	while (1)
	{
		all->str->line = get_next_line(all->fd);
		if (!all->str->line)
			break ;
		all->str->arr = ft_split(all->str->line, ' ');
		if (!all->str->arr)
			all_free(all, 1, PROCESSING);
		if (!get_map_data(all->program->map, all->str->arr, &i))
			all_free(all, 1, PROCESSING);
		free(all->str->line);
		free_array(all->str->arr);
		i++;
	}
	close(all->fd);
}

// void	clean_up_mlx(t_all *all)
// {
// 	if (!all)
// 		return ;
// 	if (all->img && all->img->img)
// 		mlx_destroy_image(all->vars->mlx, all->img->img);
// 	if (all->vars && all->vars->win)
// 		mlx_destroy_window(all->vars->mlx, all->vars->win);
// 	if (all->vars && all->vars->mlx)
// 	{
// 		mlx_destroy_display(all->vars->mlx);
// 		free(all->vars->mlx);
// 	}
// }

// int	ready_for_mlx(t_all *all)
// {
// 	all->vars->mlx = mlx_init();
// 	if (!all->vars->mlx)
// 		all_free(all, 1, PROCESSING);
// 	all->vars->win = mlx_new_window(all->vars->mlx, WIN_W, WIN_H,
// 			all->vars->title);
// 	if (!all->vars->win)
// 	{
// 		clean_up_mlx(all);
// 		all_free(all, 0, NONE);
// 		return (0);
// 	}
// 	all->img->img = mlx_new_image(all->vars->mlx, WIN_W, WIN_H);
// 	if (!all->img->img)
// 	{
// 		clean_up_mlx(all);
// 		all_free(all, 0, NONE);
// 		return (0);
// 	}
// 	return (1);
// }

// void	next_point(t_point *point, t_line *line, int *error, int *error2)
// {
// 	*error2 = *error * 2;
// 	if (*error2 > -point->dy)
// 	{
// 		*error -= point->dy;
// 		line->x0 += point->sx;
// 	}
// 	if (*error2 < point->dx)
// 	{
// 		*error += point->dx;
// 		line->y0 += point->sy;
// 	}
// }

// int	is_draw_window(int x0, int x1, int y0, int y1)
// {
// 	if ((x0 < 0 && x1 < 0) || (x0 >= WIN_W && x1 >= WIN_W)
// 		|| (y0 < 0 && y1 < 0) || (y0 >= WIN_H && y1 >= WIN_H))
// 		return (0);
// 	return (1);
// }

// void	draw_line(t_all *all, t_line *line)
// {
// 	int	error;
// 	int	error2;

// 	if (!is_draw_window(line->x0, line->x1, line->y0, line->y1))
// 		return ;
// 	all->point->dx = abs(line->x1 - line->x0);
// 	all->point->dy = abs(line->y1 - line->y0);
// 	if (line->x0 < line->x1)
// 		all->point->sx = 1;
// 	else
// 		all->point->sx = -1;
// 	if (line->y0 < line->y1)
// 		all->point->sy = 1;
// 	else
// 		all->point->sy = -1;
// 	error = all->point->dx - all->point->dy;
// 	while (1)
// 	{
// 		if (line->x0 == line->x1 && line->y0 == line->y1)
// 			break ;
// 		my_mlx_pixel_put(all->img, line->x0, line->y0, line->color);
// 		next_point(all->point, line, &error, &error2);
// 	}
// }

// void	rotate_xyz(t_program *program, double *x, double *y, double *z)
// {
// 	double	tmp_x;
// 	double	tmp_y;
// 	double	tmp_z;

// 	tmp_x = *x * cos(program->angle_z) - *y * sin(program->angle_z);
// 	tmp_y = *x * sin(program->angle_z) + *y * cos(program->angle_z);
// 	*x = tmp_x;
// 	*y = tmp_y;
// 	tmp_y = *y * cos(program->angle_x) - *z * sin(program->angle_x);
// 	tmp_z = *y * sin(program->angle_x) + *z * cos(program->angle_x);
// 	*y = tmp_y;
// 	*z = tmp_z;
// 	tmp_z = *z * cos(program->angle_y) + *x * sin(program->angle_y);
// 	tmp_x = -*z * sin(program->angle_y) + *x * cos(program->angle_y);
// 	*z = tmp_z;
// 	*x = tmp_x;
// }

// void	set_point_xyz(t_all *all, t_map *map, int i, int j)
// {
// 	all->line->color = map->z_value[i][j][1];
// 	all->point->x = (j - (map->width - 1) / 2);
// 	all->point->y = (i - (map->height - 1) / 2);
// 	all->point->z = map->z_value[i][j][0];
// }

// void	convert_to_isometric(t_point *point, t_program *program)
// {
// 	point->tmp_x = point->x;
// 	point->tmp_y = point->y;
// 	point->x = (point->tmp_x - point->tmp_y) * program->cos;
// 	point->y = (point->tmp_x + point->tmp_y) * program->sin;
// 	program->screen_x = (point->x * program->scale)
// 		+ WIN_CENTER_X + program->offset_x;
// 	program->screen_y = ((point->y - point->z) * program->scale)
// 		+ WIN_CENTER_Y + program->offset_y;
// }

// void	convert_to_isometric_next(
// 	t_point *point, t_program *program, t_line *line
// )
// {
// 	point->tmp_x = point->x;
// 	point->tmp_y = point->y;
// 	point->x = (point->tmp_x - point->tmp_y) * program->cos;
// 	point->y = (point->tmp_x + point->tmp_y) * program->sin;
// 	line->x1 = (point->x * program->scale)
// 		+ WIN_CENTER_X + program->offset_x;
// 	line->y1 = ((point->y - point->z) * program->scale)
// 		+ WIN_CENTER_Y + program->offset_y;
// }

// void	project_point(t_all *all, t_program *program, t_line *line, int flag)
// {
// 	if (flag)
// 	{
// 		rotate_xyz(program, &all->point->x, &all->point->y, &all->point->z);
// 		convert_to_isometric(all->point, program);
// 		draw_line(all, line);
// 	}
// 	else
// 	{
// 		rotate_xyz(program, &all->point->x, &all->point->y, &all->point->z);
// 		convert_to_isometric_next(all->point, program, line);
// 		draw_line(all, line);
// 	}
// }

// void	set_draw_point_xy(t_line *line, t_program *program)
// {
// 	line->x0 = program->screen_x;
// 	line->y0 = program->screen_y;
// }

// void	draw_map(t_all *all, t_map *map, t_program *program, t_line *line)
// {
// 	int		i;
// 	int		j;

// 	i = -1;
// 	while (++i < map->height)
// 	{
// 		j = -1;
// 		while (++j < map->width)
// 		{
// 			set_point_xyz(all, map, i, j);
// 			project_point(all, program, line, 1);
// 			if (j < map->width - 1)
// 			{
// 				set_draw_point_xy(line, program);
// 				set_point_xyz(all, map, i, j + 1);
// 				project_point(all, program, line, 0);
// 			}
// 			if (i < map->height - 1)
// 			{
// 				set_draw_point_xy(line, program);
// 				set_point_xyz(all, map, i + 1, j);
// 				project_point(all, program, line, 0);
// 			}
// 		}
// 	}
// }

// void	clear_image(t_data *img)
// {
// 	ft_memset(img->addr, 0, WIN_W * WIN_H * (img->bits_per_pixel / 8));
// }

// void	zoomzoom(t_program *program, int keycode)
// {
// 	if (keycode == PLUS_KEY)
// 	{
// 		program->scale += 3;
// 		if (program->scale > 1000)
// 			program->scale = 1000;
// 	}
// 	else if (keycode == MINUS_KEY)
// 	{
// 		program->scale -= 3;
// 		if (program->scale < 2)
// 			program->scale = 2;
// 	}
// }

// void	wasd(t_program *program, int keycode)
// {
// 	if (keycode == W_KEY)
// 		program->offset_y += 5;
// 	else if (keycode == S_KEY)
// 		program->offset_y -= 5;
// 	else if (keycode == D_KEY)
// 		program->offset_x -= 5;
// 	else if (keycode == A_KEY)
// 		program->offset_x += 5;
// }

// void	rotate_axis(t_program *program, int keycode)
// {
// 	if (keycode == ARROW_RIGHT)
// 		program->angle_y -= 0.1;
// 	else if (keycode == ARROW_LEFT)
// 		program->angle_y += 0.1;
// 	else if (keycode == ARROW_DOWN)
// 		program->angle_x -= 0.1;
// 	else if (keycode == ARROW_UP)
// 		program->angle_x += 0.1;
// 	else if (keycode == X_KEY)
// 		program->angle_z -= 0.1;
// 	else if (keycode == Z_KEY)
// 		program->angle_z += 0.1;
// }

// void	reset_position(t_program *program)
// {
// 	program->scale = 10;
// 	program->offset_x = 0;
// 	program->offset_y = 0;
// 	program->angle_x = 0;
// 	program->angle_y = 0;
// 	program->angle_z = 0;
// }

// void	put_instructions_to_window(t_vars *vars)
// {
// 	mlx_string_put(vars->mlx, vars->win, 10, 10,
// 		0x00FFFF00, vars->title);
// 	mlx_string_put(vars->mlx, vars->win, 10, 30,
// 		0x00FFFF00, "Zoom: -/+");
// 	mlx_string_put(vars->mlx, vars->win, 10, 50,
// 		0x00FFFF00, "Transition: WASD");
// 	mlx_string_put(vars->mlx, vars->win, 10, 70,
// 		0x00FFFF00, "Rotattion: X/Y Arrow Key, Z Arrow Z/X");
// 	mlx_string_put(vars->mlx, vars->win, 10, 90,
// 		0x00FFFF00, "Reset: R");
// 	mlx_string_put(vars->mlx, vars->win, 10, 110,
// 		0x00FFFF00, "Close: ESC");
// }

// int	move_fdf(int keycode, t_all *all)
// {
// 	if (keycode == ESC_KEY)
// 	{
// 		clean_up_mlx(all);
// 		all_free(all, 1, NONE);
// 	}
// 	else if (keycode == PLUS_KEY || keycode == MINUS_KEY)
// 		zoomzoom(all->program, keycode);
// 	else if (keycode == W_KEY || keycode == A_KEY
// 		|| keycode == S_KEY || keycode == D_KEY)
// 		wasd(all->program, keycode);
// 	else if (keycode == ARROW_RIGHT || keycode == ARROW_LEFT
// 		|| keycode == ARROW_UP || keycode == ARROW_DOWN
// 		|| keycode == X_KEY || keycode == Z_KEY)
// 		rotate_axis(all->program, keycode);
// 	else if (keycode == R_KEY)
// 		reset_position(all->program);
// 	clear_image(all->program->img);
// 	draw_map(all, all->map, all->program, all->line);
// 	mlx_put_image_to_window(all->vars->mlx, all->vars->win,
// 		all->img->img, 0, 0);
// 	put_instructions_to_window(all->vars);
// 	return (0);
// }

// int	close_window(t_all *all)
// {
// 	clean_up_mlx(all);
// 	all_free(all, 1, NONE);
// 	return (0);
// }

void	start_fdf(t_all *all)
{
	all->img->addr = mlx_get_data_addr(all->img->img, &all->img->bits_per_pixel,
			&all->img->line_length, &all->img->endian);
	clear_image(all->program->img);
	draw_map(all, all->map, all->program, all->line);
	mlx_put_image_to_window(all->vars->mlx, all->vars->win, all->img->img,
		0, 0);
	put_instructions_to_window(all->vars);
	mlx_string_put(all->vars->mlx, all->vars->win, 10, 10,
		0x00FF99FF, all->vars->title);
	mlx_hook(all->vars->win, ON_KEY_DOWN, 1L << 0, move_fdf, all);
	mlx_hook(all->vars->win, ON_DESTROY, 0, close_window, all);
	mlx_loop(all->vars->mlx);
	clean_up_mlx(all);
	all_free(all, 0, NONE);
}

int	main(int ac, char **av)
{
	t_all	*all;

	if (!validate_arg(ac, av[1]))
		throwing_error(INVALID_ARG);
	init_all_structure(&all, av[1]);
	read_map_data(all);
	if (!ready_for_mlx(all))
		throwing_error(PROCESSING);
	start_fdf(all);
	clean_up_mlx(all);
	all_free(all, 0, NONE);
}
