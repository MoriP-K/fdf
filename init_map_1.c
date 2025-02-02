/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoriyam <kmoriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 22:23:11 by kmoriyam          #+#    #+#             */
/*   Updated: 2025/02/02 14:48:59 by kmoriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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

void	init_map_data(t_map *map)
{
	map->z_value = NULL;
	map->check_width = NULL;
	map->height = 0;
	map->width = 0;
}

t_map	*init_map(t_all *all)
{
	t_map	*map;

	map = (t_map *)malloc(sizeof(t_map));
	if (!map)
		return (NULL);
	init_map_data(map);
	if (!get_map_size(all, map))
	{
		free(map);
		all_free(all, 1, INVALID_ARG);
	}
	map->z_value = malloc(sizeof(int **) * map->height);
	if (!map->z_value)
	{
		free(map);
		all_free(all, 0, NONE);
		return (NULL);
	}
	return (map);
}
