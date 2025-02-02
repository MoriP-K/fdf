/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoriyam <kmoriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 20:32:31 by kmoriyam          #+#    #+#             */
/*   Updated: 2025/02/02 14:30:26 by kmoriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	next_point(t_point *point, t_line *line, int *error, int *error2)
{
	*error2 = *error * 2;
	if (*error2 > -point->dy)
	{
		*error -= point->dy;
		line->x0 += point->sx;
	}
	if (*error2 < point->dx)
	{
		*error += point->dx;
		line->y0 += point->sy;
	}
}

int	is_draw_window(int x0, int x1, int y0, int y1)
{
	if ((x0 < 0 && x1 < 0) || (x0 >= WIN_W && x1 >= WIN_W)
		|| (y0 < 0 && y1 < 0) || (y0 >= WIN_H && y1 >= WIN_H))
		return (0);
	return (1);
}

void	draw_line(t_all *all, t_line *line)
{
	int	error;
	int	error2;

	if (!is_draw_window(line->x0, line->x1, line->y0, line->y1))
		return ;
	all->point->dx = abs(line->x1 - line->x0);
	all->point->dy = abs(line->y1 - line->y0);
	if (line->x0 < line->x1)
		all->point->sx = 1;
	else
		all->point->sx = -1;
	if (line->y0 < line->y1)
		all->point->sy = 1;
	else
		all->point->sy = -1;
	error = all->point->dx - all->point->dy;
	while (1)
	{
		my_mlx_pixel_put(all->img, line->x0, line->y0, line->color);
		if (line->x0 == line->x1 && line->y0 == line->y1)
			break ;
		next_point(all->point, line, &error, &error2);
	}
}
