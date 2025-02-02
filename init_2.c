/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoriyam <kmoriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 21:54:32 by kmoriyam          #+#    #+#             */
/*   Updated: 2025/02/02 13:50:48 by kmoriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	set_default_value(t_program *program)
{
	program->scale = 10;
	program->offset_x = 0;
	program->offset_y = 0;
	program->angle_x = 0;
	program->angle_y = 0;
	program->angle_z = 0;
	program->screen_x = 0.0;
	program->screen_y = 0.0;
	program->cos = cos(M_PI / 6);
	program->sin = sin(M_PI / 6);
}

t_program	*init_program(t_vars *vars, t_data *img, t_map *map)
{
	t_program	*program;

	program = (t_program *)malloc(sizeof(t_program));
	if (!program)
		return (NULL);
	program->vars = vars;
	program->img = img;
	program->map = map;
	set_default_value(program);
	return (program);
}

t_data	*init_data(void)
{
	t_data	*data;

	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	return (data);
}

t_vars	*init_vars(t_program *program, char *file)
{
	t_vars	*vars;

	vars = (t_vars *)malloc(sizeof(t_vars));
	if (!vars)
		return (NULL);
	vars->program = program;
	vars->title = file;
	return (vars);
}

t_str	*init_str(void)
{
	t_str	*str;

	str = (t_str *)malloc(sizeof(t_str));
	if (!str)
		return (NULL);
	str->arr = NULL;
	str->line = NULL;
	return (str);
}
