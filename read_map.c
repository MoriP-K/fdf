/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoriyam <kmoriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 20:34:13 by kmoriyam          #+#    #+#             */
/*   Updated: 2025/02/02 14:28:47 by kmoriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	assign_data_and_color(int *z_value, char *arr)
{
	char	**split_arr;

	if (!ft_strchr(arr, ','))
	{
		z_value[0] = ft_atoi(arr);
		z_value[1] = hex_to_int("0x0000FFFF");
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
		return (1);
	}
	free_array(split_arr);
	return (0);
}

int	get_data_and_color(int **z_value, char **arr, int *width)
{
	if (!arr[*width])
		return (0);
	z_value[*width] = malloc(sizeof(int) * 2);
	if (!z_value[*width])
		return (0);
	if (!assign_data_and_color(z_value[*width], arr[*width]))
		return (0);
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
