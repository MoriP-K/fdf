/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoriyam <kmoriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 20:31:04 by kmoriyam          #+#    #+#             */
/*   Updated: 2025/02/01 21:53:45 by kmoriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	rotate_xyz(t_program *program, double *x, double *y, double *z)
{
	double	tmp_x;
	double	tmp_y;
	double	tmp_z;

	tmp_x = *x * cos(program->angle_z) - *y * sin(program->angle_z);
	tmp_y = *x * sin(program->angle_z) + *y * cos(program->angle_z);
	*x = tmp_x;
	*y = tmp_y;
	tmp_y = *y * cos(program->angle_x) - *z * sin(program->angle_x);
	tmp_z = *y * sin(program->angle_x) + *z * cos(program->angle_x);
	*y = tmp_y;
	*z = tmp_z;
	tmp_z = *z * cos(program->angle_y) + *x * sin(program->angle_y);
	tmp_x = -*z * sin(program->angle_y) + *x * cos(program->angle_y);
	*z = tmp_z;
	*x = tmp_x;
}

void	set_point_xyz(t_all *all, t_map *map, int i, int j)
{
	all->line->color = map->z_value[i][j][1];
	all->point->x = (j - (map->width - 1) / 2);
	all->point->y = (i - (map->height - 1) / 2);
	all->point->z = map->z_value[i][j][0];
}
