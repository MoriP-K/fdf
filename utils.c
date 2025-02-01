/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoriyam <kmoriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 22:22:05 by kmoriyam          #+#    #+#             */
/*   Updated: 2025/02/01 23:14:50 by kmoriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ready_for_mlx(t_all *all)
{
	all->vars->mlx = mlx_init();
	if (!all->vars->mlx)
		all_free(all, 1, PROCESSING);
	all->vars->win = mlx_new_window(all->vars->mlx, WIN_W, WIN_H,
			all->vars->title);
	if (!all->vars->win)
	{
		clean_up_mlx(all);
		all_free(all, 0, NONE);
		return (0);
	}
	all->img->img = mlx_new_image(all->vars->mlx, WIN_W, WIN_H);
	if (!all->img->img)
	{
		clean_up_mlx(all);
		all_free(all, 0, NONE);
		return (0);
	}
	return (1);
}

void	put_instructions_to_window(t_vars *vars)
{
	mlx_string_put(vars->mlx, vars->win, 10, 10,
		0x00FF99FF, vars->title);
	mlx_string_put(vars->mlx, vars->win, 10, 30,
		0x00FFFF00, "Zoom: -/+");
	mlx_string_put(vars->mlx, vars->win, 10, 50,
		0x00FFFF00, "Transition: WASD");
	mlx_string_put(vars->mlx, vars->win, 10, 70,
		0x00FFFF00, "Rotattion: X/Y Arrow Key, Z Arrow Z/X");
	mlx_string_put(vars->mlx, vars->win, 10, 90,
		0x00FFFF00, "Reset: R");
	mlx_string_put(vars->mlx, vars->win, 10, 110,
		0x00FFFF00, "Close: ESC");
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	if ((unsigned int)x >= WIN_W || (unsigned int)y >= WIN_H)
		return ;
	*(unsigned int *)(data->addr + (y * data->line_length \
		+ x * (data->bits_per_pixel / 8))) = color;
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
