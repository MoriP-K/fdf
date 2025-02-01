/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_fdf.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoriyam <kmoriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 21:57:52 by kmoriyam          #+#    #+#             */
/*   Updated: 2025/02/01 22:35:22 by kmoriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	clear_image(t_data *img)
{
	ft_memset(img->addr, 0, WIN_W * WIN_H * (img->bits_per_pixel / 8));
}

int	close_window(t_all *all)
{
	clean_up_mlx(all);
	all_free(all, 1, NONE);
	return (0);
}

void	clean_up_mlx(t_all *all)
{
	if (!all)
		return ;
	if (all->img && all->img->img)
		mlx_destroy_image(all->vars->mlx, all->img->img);
	if (all->vars && all->vars->win)
		mlx_destroy_window(all->vars->mlx, all->vars->win);
	if (all->vars && all->vars->mlx)
	{
		mlx_destroy_display(all->vars->mlx);
		free(all->vars->mlx);
	}
}
