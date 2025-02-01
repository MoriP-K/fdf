/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoriyam <kmoriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 20:28:57 by kmoriyam          #+#    #+#             */
/*   Updated: 2025/02/01 23:39:12 by kmoriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	convert_to_isometric(t_point *point, t_program *program)
{
	point->tmp_x = point->x;
	point->tmp_y = point->y;
	point->x = (point->tmp_x - point->tmp_y) * program->cos;
	point->y = (point->tmp_x + point->tmp_y) * program->sin;
	program->screen_x = (point->x * program->scale) \
		+ WIN_CENTER_X + program->offset_x;
	program->screen_y = ((point->y - point->z) * program->scale) \
		+ WIN_CENTER_Y + program->offset_y;
}

void	convert_to_isometric_next(
	t_point *point, t_program *program, t_line *line
)
{
	point->tmp_x = point->x;
	point->tmp_y = point->y;
	point->x = (point->tmp_x - point->tmp_y) * program->cos;
	point->y = (point->tmp_x + point->tmp_y) * program->sin;
	line->x1 = (point->x * program->scale) \
		+ WIN_CENTER_X + program->offset_x;
	line->y1 = ((point->y - point->z) * program->scale) \
		+ WIN_CENTER_Y + program->offset_y;
}

void	project_point(t_all *all, t_program *program, t_line *line, int flag)
{
	if (flag)
	{
		rotate_xyz(program, &all->point->x, &all->point->y, &all->point->z);
		convert_to_isometric(all->point, program);
		draw_line(all, line);
	}
	else
	{
		rotate_xyz(program, &all->point->x, &all->point->y, &all->point->z);
		convert_to_isometric_next(all->point, program, line);
		draw_line(all, line);
	}
}

void	set_draw_point_xy(t_line *line, t_program *program)
{
	line->x0 = program->screen_x;
	line->y0 = program->screen_y;
}

void	draw_map(t_all *all, t_map *map, t_program *program, t_line *line)
{
	int		i;
	int		j;

	i = -1;
	while (++i < map->height)
	{
		j = -1;
		while (++j < map->width)
		{
			set_point_xyz(all, map, i, j);
			project_point(all, program, line, 1);
			if (j < map->width - 1)
			{
				set_draw_point_xy(line, program);
				set_point_xyz(all, map, i, j + 1);
				project_point(all, program, line, 0);
			}
			if (i < map->height - 1)
			{
				set_draw_point_xy(line, program);
				set_point_xyz(all, map, i + 1, j);
				project_point(all, program, line, 0);
			}
		}
	}
}
