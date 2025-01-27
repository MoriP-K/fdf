/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_new.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoriyam <kmoriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 15:04:54 by kmoriyam          #+#    #+#             */
/*   Updated: 2025/01/27 20:43:39 by kmoriyam         ###   ########.fr       */
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
	char	*dst;

	if ((unsigned int)x >= WIN_WIDTH || (unsigned int)y >= WIN_HEIGHT)
		return ;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

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

void	free_map(t_map *map)
{
	int	i;
	int	j;

	if (!map)
		return ;
	i = 0;
	if (map->z_value)
	{
		while (i < map->height)
		{
			if (map->z_value[i])
			{
				j = 0;
				while (j < map->width && map->z_value[i][j])
				{
					free(map->z_value[i][j]);
					j++;
				}
				free(map->z_value[i]);
			}
			i++;
		}
		free(map->z_value);
	}
	free(map);
}

void	all_free(t_all *all, int flag)
{
	if (!all)
		return ;
	if (all->program)
		free(all->program);
	if (all->img)
		free(all->img);
	if (all->vars)
		free(all->vars);
	if (all->str)
	{
		if (all->str->line)
			free(all->str->line);
		free(all->str);
	}
	if (all->map)
		free_map(all->map);
	if (all)
		free(all);
	if (flag)
		exit (EXIT_FAILURE);
}

void	set_default_value(t_program *program)
{
	program->scale = 10;
	program->offset_x = 0;
	program->offset_y = 0;
	program->angle_x = 0;
	program->angle_y = 0;
	program->angle_z = 0;
	program->projected_x = 0.0;
	program->projected_y = 0.0;
	program->cos = cos(M_PI / 6);
	program->sin = sin(M_PI / 6);
}

t_program	*init_program(t_vars *vars, t_data *img, t_map *map)
{
	t_program	*program;

	program = (t_program *)malloc(sizeof(t_program));
	if (!program)
		return (NULL);
	program->vars = vars;
	program->img = img;
	program->map = map;
	set_default_value(program);
	return (program);
}

t_data	*init_data(void)
{
	t_data	*data;

	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	return (data);
}

t_vars	*init_vars(t_program *program, char *file)
{
	t_vars	*vars;

	vars = (t_vars *)malloc(sizeof(t_vars));
	if (!vars)
		return (NULL);
	vars->program = program;
	vars->title = file;
	return (vars);
}

t_str	*init_str(void)
{
	t_str	*str;

	str = (t_str *)malloc(sizeof(t_str));
	if (!str)
		return (NULL);
	str->arr = NULL;
	str->line = NULL;
	return (str);
}

int	get_map_height(int fd)
{
	int			height;
	char		*line;

	height = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		free(line);
		height++;
	}
	close(fd);
	return (height);
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

int	clean_up_width(int *check)
{
	int	width;

	width = check[0];
	free(check);
	return (width);
}

int	get_map_width(int fd, char *file, int height, int **check)
{
	char	*line;
	int		i;

	fd = open(file, O_RDONLY);
	*check = malloc(sizeof(int) * height);
	if (fd == -1 || !*check)
		return (-1);
	i = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		(*check)[i] = count_word(line, ' ');
		free(line);
		if (i > 0 && (*check)[i] >= 2 && (*check)[i - 1] != (*check)[i])
		{
			free(*check);
			close(fd);
			return (-1);
		}
		i++;
	}
	close(fd);
	return (clean_up_width(*check));
}

t_map	*get_map_size(t_all *all, t_map *map)
{
	map->height = get_map_height(all->fd);
	map->width = get_map_width(all->fd, all->file, map->height,
			&map->check_width);
	if (map->width <= 1 || map->height <= 1)
		return (NULL);
	return (map);
}

t_map	*init_map(t_all *all)
{
	t_map	*map;

	map = (t_map *)malloc(sizeof(t_map));
	if (!map)
		return (NULL);
	if (!get_map_size(all, map))
	{
		free(map);
		all_free(all, 1);
	}
	map->z_value = malloc(sizeof(int **) * map->height);
	if (!map->z_value)
	{
		free(map);
		all_free(all, 1);
	}
	return (map);
}

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
	(*all)->fd = open(file, O_RDONLY);
	if (!(*all)->program || !(*all)->img || !(*all)->vars
		|| !(*all)->str || !(*all)->map || (*all)->fd == -1)
		all_free(*all, 1);
}

unsigned int	hex_to_int(const char *hex_str)
{
	unsigned int	num;
	size_t			i;

	num = 0;
	i = 2;
	while (hex_str[i] && i < 10)
	{
		num = num * 16;
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

int	assign_data_and_color(int *z_value, char *arr)
{
	char	**split_arr;

	if (!ft_strchr(arr, ','))
	{
		z_value[0] = ft_atoi(arr);
		z_value[1] = hex_to_int("0x0000FFFF");
		printf("z_value = h:%d, c: %d\n", z_value[0], z_value[1]);
		return (1);
	}
	split_arr = ft_split(arr, ',');
	if (!split_arr)
		return (0);
	z_value[0] = ft_atoi(split_arr[0]);
	if (ft_strlen(split_arr[1]) > 2 && split_arr[1][0] == '0' &&
		(split_arr[1][1] == 'x' || split_arr[1][1] == 'X'))
	{
		z_value[1] = hex_to_int(split_arr[1]);
		free_array(split_arr);
		printf("z_value = h:%d, c: %d\n", z_value[0], z_value[1]);
		return (1);
	}
	free(split_arr);
	return (0);
}

int	get_data_and_color(int **z_value, char **arr, int *width)
{
	z_value[*width] = malloc(sizeof(int) * 2);
	if (!z_value)
		return (0);
	if (arr[*width])
	{
		if (!assign_data_and_color(z_value[*width], arr[*width]))
			return (0);
	}
	return (1);
}

int	get_map_data(t_map *map, char **arr, int *height)
{
	int	j;

	map->z_value[*height] = malloc(sizeof(int *) * map->width);
	if (!map->z_value[*height])
		return (0);
	j = 0;
	while (j < map->width)
	{
		if (!get_data_and_color(map->z_value[*height], arr, &j))
			return (0);
		j++;
	}
	return (1);
}

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
			all_free(all, 1);
		if (!get_map_data(all->program->map, all->str->arr, &i))
			all_free(all, 1);
		free(all->str->line);
		free_array(all->str->arr);
		i++;
	}
	close(all->fd);
}

int	main(int ac, char **av)
{
	t_all	*all;

	if (!validate_arg(ac, av[1]))
	{
		write(2, "Invalid Argument.\n", 18);
		return (1);
	}
	init_all_structure(&all, av[1]);
	read_map_data(all);
	all_free(all, 0);
}
