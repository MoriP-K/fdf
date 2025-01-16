/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoriyam <kmoriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 20:23:33 by kmoriyam          #+#    #+#             */
/*   Updated: 2025/01/16 22:40:29 by kmoriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_linux/mlx.h"
#include "types.h"
#include "gnl/get_next_line.h"
#include "libft/libft.h"
#include <math.h>

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (0 <= x && x < 1920 && 0 <= y && y < 1080)
	{
		dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
		*(unsigned int*)dst = color;
	}
}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int	get_t(int trgb)
{
	return ((trgb >> 24) & 0xFF);
}

int	get_r(int trgb)
{
	return ((trgb >> 16) & 0xFF);
}

int	get_g(int trgb)
{
	return ((trgb >> 8) & 0xFF);
}

int	get_b(int trgb)
{
	return (trgb & 0xFF);
}

void	draw_line(t_data *data, t_line *line)
{
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	error;
	int	error2;

	dx = abs(line->x1 - line->x0);
	dy = abs(line->y1 - line->y0);
	if (line->x0 < line->x1)
		sx = 1;
	else
		sx = -1;
	if (line->y0 < line->y1)
		sy = 1;
	else
		sy = -1;
	error = dx - dy;
	while (1)
	{
		my_mlx_pixel_put(data, line->x0, line->y0, line->color);
		if (line->x0 == line->x1 && line->y0 == line->y1)
			break ;
		error2 = error * 2;
		if (error2 > -dy)
		{
			error -= dy;
			line->x0 += sx;
		}
		if (error2 < dx)
		{
			error += dx;
			line->y0 += sy;
		}
	}
}

void	draw_map(t_data *img, t_map *map)
{
	int	i;
	int	j;
	t_line	line;
	const double	angle_x = 0.785398;
	const double	angle_y = 0.523599;
	int	iso_x;
	int	iso_y;
	int	next_iso_x;
	int	next_iso_y;
	const int	scale = 30;

	i = 0;
	line.color  = 0x00FFFFFF;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width[i])
		{
			iso_x = (j - i) * cos(angle_x) * scale;
			iso_y = ((j + i) * sin(angle_y) - map->z_value[i][j][0]) * scale;
			line.x0 = iso_x + 960 - ((map->width[0] - 1) * scale / 2);
			line.y0 = iso_y + 540 - ((map->height - 1) * scale / 2);
			my_mlx_pixel_put(img, line.x0, line.y0,line.color);
			
			if (j < map->width[i] - 1)
			{
				next_iso_x = ((j + 1) - i) * cos(angle_x) * scale;
				next_iso_y = (((j + 1) + i) * sin(angle_y) - map->z_value[i][j + 1][0]) * scale;
				line.x1 = next_iso_x + 960 - ((map->width[0] - 1) * scale / 2);
				line.y1 = next_iso_y + 540 - ((map->height - 1) * scale / 2);
				draw_line(img, &line);
			}
			
			line.x0 = iso_x + 960 - ((map->width[0] - 1) * scale / 2);
			line.y0 = iso_y + 540 - ((map->height - 1) * scale / 2);
			
			if (i < map->height - 1)
			{
				next_iso_x = (j - (i + 1)) * cos(angle_x) * scale;
				next_iso_y = ((j + (i + 1)) * sin(angle_y) - map->z_value[i + 1][j][0]) * scale;
				line.x1 = next_iso_x + 960 - ((map->width[0] - 1) * scale / 2);
				line.y1 = next_iso_y + 540 - ((map->height - 1) * scale / 2);
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
		return (NULL);
	i = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		map->width[i] = count_word(line, ' ');
		free(line);
		printf("width[%d]: %d\n", i, map->width[i]);
		i++;
	}
	printf("height: %d\n", map->height);
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
	i = 0;
	if (map->z_value)
	{
		while (i < map->height)
		{
			if (map->z_value[i])
			{
				j = 0;
				while (j < map->width[j])
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
	free(map->width);
	free(map);
}

void	all_free(t_map *map, char **array, char *line)
{
	if (map)
		free_map(map);
	if (array)
		free_array(array);
	if (line)
		free(line);
}

t_map	*init_map(char *file, int fd)
{
	t_map	*map;

	map = (t_map *)malloc(sizeof(t_map));
	if (!map)
		return (NULL);
	map = get_map_size(map, file, fd);
	if (!map)
		return (NULL);
	return (map);
}

void	display_map(t_map *map)
{
	int	i;
	int	j;

	if (!map)
    {
        printf("Map is NULL\n");
        return;
    }
    printf("Z-values and colors:\n");
	printf("Map dimensions: height = %d\n", map->height);
	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width[i])
		{
			printf("width = %d ", map->width[i]);
			if (map->z_value && map->z_value[i] && map->z_value[i][j])
                printf("[%d, %d] \n", map->z_value[i][j][0], map->z_value[i][j][1]);
            else
                printf("[NULL] ");
			j++;
		}
		printf("\n");
		i++;
	}
}

int	main(int ac, char **av)
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;

	int		fd;
	char	*line;
	char	**array;
	char	**split_arr;
	t_map	*map;
	int		i;
	int		j;
	int		wc;

	if (ac > 2)
		return (1);
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
	{
		write(1, "Error\n", 6);
		return (1);
	}
	map = init_map(av[1], fd);
	if (!map)
	{
		write(1, "Error\n", 6);
		return (1);
	}
	// z_valueの1次元目のメモリ確保
	map->z_value = malloc(sizeof(int **) * map->height);
	if (!map->z_value)
	{
		all_free(map, NULL, NULL);
		return (1);
	}

	// 2回目の読み込みでデータを格納
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
		printf("\nProcessing line[%d] = %s", i, line);
		array = ft_split(line, ' ');
		if (!array)
		{
			all_free(map, NULL, line);
			return (1);
		}
		// z_valueの2次元目のメモリ確保
		map->z_value[i] = malloc(sizeof(int *) * map->width[i]);
		if (!map->z_value[i])
		{
			all_free(map, array, line);
			return (1);
		}
		j = 0;
		while (j < wc)
		{
			map->z_value[i][j] = malloc(sizeof(int) * 2); // 高さと色の分をmallocする
			if (!map->z_value[i][j])
			{
				all_free(map, array, line);
				return (1);
			}
			// 高さと色の情報を入れていく
			if (array[j])
			{
				if (!ft_strchr(array[j], ','))
				{
					map->z_value[i][j][0] = ft_atoi(array[j]); 
					map->z_value[i][j][1] = 0;
				}
				else
				{
					split_arr = ft_split(array[j], ',');
					if (!split_arr)
					{
						all_free(map, NULL, array[j]);
						return (1);
					}
					map->z_value[i][j][0] = ft_atoi(split_arr[0]);
					map->z_value[i][j][1] = ft_atoi(split_arr[1]); 
					all_free(NULL, split_arr, NULL);
				}
				//カンマが来るまで数字に変換する、ポインタをずらしてそれを色に変換する
				
				// 色の情報を入れていく  map->z_value[i][j][1]
				printf("Stored value at [%d][%d] = h:%d, c: %d\n", i, j, map->z_value[i][j][0], map->z_value[i][j][1]);
			}
			j++;
		}
		all_free(NULL, array, line);
		i++;
	}
	close(fd);

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello World!");
	img.img = mlx_new_image(mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	i = 0;
	draw_map(&img, map);
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
	// display structure
	printf("\nFinal structure:\n");
	display_map(map);
	all_free(map, NULL, NULL);
}
