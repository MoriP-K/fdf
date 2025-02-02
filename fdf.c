/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoriyam <kmoriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 15:04:54 by kmoriyam          #+#    #+#             */
/*   Updated: 2025/02/02 14:20:23 by kmoriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	validate_arg(int ac, char *file_name)
{
	int	len;

	if (ac != 2)
		return (0);
	len = ft_strlen(file_name);
	if (len <= 4)
		return (0);
	len--;
	if (file_name[len - 3] != '.' || file_name[len - 2] != 'f'
		|| file_name[len - 1] != 'd' || file_name[len] != 'f')
		return (0);
	return (1);
}

void	init_all_structure(t_all **all, char *file)
{
	*all = (t_all *)malloc(sizeof(t_all));
	if (!*all)
		exit(EXIT_FAILURE);
	ft_memset(*all, 0, sizeof(t_all));
	(*all)->fd = open(file, O_RDONLY);
	if ((*all)->fd == -1)
		exit (EXIT_FAILURE);
	(*all)->file = file;
	(*all)->img = init_data();
	(*all)->map = init_map(*all);
	(*all)->vars = init_vars(NULL, file);
	(*all)->program = init_program((*all)->vars, (*all)->img, (*all)->map);
	(*all)->vars->program = (*all)->program;
	(*all)->str = init_str();
	(*all)->line = init_line();
	(*all)->point = init_point();
	(*all)->fd = open(file, O_RDONLY);
	if (!(*all)->program || !(*all)->img || !(*all)->vars || !(*all)->str
		|| !(*all)->map || !(*all)->line || !(*all)->point || (*all)->fd == -1)
		all_free(*all, 1, PROCESSING);
}

void	read_map_data(t_all *all)
{
	int		i;

	i = 0;
	while (1)
	{
		all->str->line = get_next_line(all->fd);
		if (!all->str->line)
			break ;
		all->str->arr = ft_split(all->str->line, ' ');
		if (!all->str->arr)
			all_free(all, 1, PROCESSING);
		if (!get_map_data(all->program->map, all->str->arr, &i))
			all_free(all, 1, PROCESSING);
		free(all->str->line);
		free_array(all->str->arr);
		i++;
	}
	close(all->fd);
}

void	start_fdf(t_all *all)
{
	all->img->addr = mlx_get_data_addr(all->img->img, &all->img->bits_per_pixel,
			&all->img->line_length, &all->img->endian);
	clear_image(all->program->img);
	draw_map(all, all->map, all->program, all->line);
	mlx_put_image_to_window(all->vars->mlx, all->vars->win, all->img->img,
		0, 0);
	put_instructions_to_window(all->vars);
	mlx_string_put(all->vars->mlx, all->vars->win, 10, 10,
		0x00FF99FF, all->vars->title);
	mlx_hook(all->vars->win, ON_KEY_DOWN, 1L << 0, move_fdf, all);
	mlx_hook(all->vars->win, ON_DESTROY, 0, close_window, all);
	mlx_loop(all->vars->mlx);
	clean_up_mlx(all);
	all_free(all, 0, NONE);
}

int	main(int ac, char **av)
{
	t_all	*all;

	if (!validate_arg(ac, av[1]))
		throwing_error(INVALID_ARG);
	init_all_structure(&all, av[1]);
	read_map_data(all);
	if (!ready_for_mlx(all))
		throwing_error(PROCESSING);
	start_fdf(all);
	clean_up_mlx(all);
	all_free(all, 0, NONE);
}
