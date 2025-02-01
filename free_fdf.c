/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_fdf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoriyam <kmoriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 22:18:56 by kmoriyam          #+#    #+#             */
/*   Updated: 2025/02/01 23:13:54 by kmoriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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

void	throwing_error(int error_no)
{
	if (error_no == INVALID_ARG)
		ft_putstr_fd("Invalid Argument.\n", 2);
	else if (error_no == PROCESSING)
		ft_putstr_fd("Error.\n", 2);
	exit(EXIT_FAILURE);
}

void	all_free(t_all *all, int flag, int errorno)
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
	if (all->line)
		free(all->line);
	if (all->point)
		free(all->point);
	if (all)
		free(all);
	if (flag)
		throwing_error(errorno);
}
