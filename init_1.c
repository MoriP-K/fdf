/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoriyam <kmoriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 20:35:52 by kmoriyam          #+#    #+#             */
/*   Updated: 2025/02/01 22:34:52 by kmoriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_line	*init_line(void)
{
	t_line	*line;

	line = (t_line *)malloc(sizeof(t_line));
	if (!line)
		return (NULL);
	line->x0 = 0;
	line->x1 = 0;
	line->y0 = 0;
	line->y1 = 0;
	line->color = 0;
	return (line);
}

t_point	*init_point(void)
{
	t_point	*point;

	point = (t_point *)malloc(sizeof(t_point));
	if (!point)
		return (NULL);
	point->x = 0;
	point->y = 0;
	point->z = 0;
	point->dx = 0;
	point->dy = 0;
	point->sx = 0;
	point->sy = 0;
	point->tmp_x = 0;
	point->tmp_y = 0;
	return (point);
}
