/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoriyam <kmoriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 20:10:16 by kmoriyam          #+#    #+#             */
/*   Updated: 2025/02/01 22:37:09 by kmoriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	zoomzoom(t_program *program, int keycode)
{
	if (keycode == PLUS_KEY)
	{
		program->scale += 3;
		if (program->scale > 1000)
			program->scale = 1000;
	}
	else if (keycode == MINUS_KEY)
	{
		program->scale -= 3;
		if (program->scale < 2)
			program->scale = 2;
	}
}

void	wasd(t_program *program, int keycode)
{
	if (keycode == W_KEY)
		program->offset_y += 5;
	else if (keycode == S_KEY)
		program->offset_y -= 5;
	else if (keycode == D_KEY)
		program->offset_x -= 5;
	else if (keycode == A_KEY)
		program->offset_x += 5;
}

void	rotate_axis(t_program *program, int keycode)
{
	if (keycode == ARROW_RIGHT)
		program->angle_y += 0.1;
	else if (keycode == ARROW_LEFT)
		program->angle_y -= 0.1;
	else if (keycode == ARROW_DOWN)
		program->angle_x -= 0.1;
	else if (keycode == ARROW_UP)
		program->angle_x += 0.1;
	else if (keycode == X_KEY)
		program->angle_z -= 0.1;
	else if (keycode == Z_KEY)
		program->angle_z += 0.1;
}

void	reset_position(t_program *program)
{
	program->scale = 10;
	program->offset_x = 0;
	program->offset_y = 0;
	program->angle_x = 0;
	program->angle_y = 0;
	program->angle_z = 0;
}

int	move_fdf(int keycode, t_all *all)
{
	if (keycode == ESC_KEY)
	{
		clean_up_mlx(all);
		all_free(all, 1, NONE);
	}
	else if (keycode == PLUS_KEY || keycode == MINUS_KEY)
		zoomzoom(all->program, keycode);
	else if (keycode == W_KEY || keycode == A_KEY
		|| keycode == S_KEY || keycode == D_KEY)
		wasd(all->program, keycode);
	else if (keycode == ARROW_RIGHT || keycode == ARROW_LEFT
		|| keycode == ARROW_UP || keycode == ARROW_DOWN
		|| keycode == X_KEY || keycode == Z_KEY)
		rotate_axis(all->program, keycode);
	else if (keycode == R_KEY)
		reset_position(all->program);
	clear_image(all->program->img);
	draw_map(all, all->map, all->program, all->line);
	mlx_put_image_to_window(all->vars->mlx, all->vars->win,
		all->img->img, 0, 0);
	put_instructions_to_window(all->vars);
	return (0);
}
