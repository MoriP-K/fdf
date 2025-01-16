/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoriyam <kmoriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 15:04:39 by kmoriyam          #+#    #+#             */
/*   Updated: 2025/01/15 19:28:15 by kmoriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

typedef struct s_map
{
	// int	**map;
	int	*width;
	int	height;
	int	***z_value;
}	t_map;

typedef struct	s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	t_map	**map;
}				t_data;

typedef struct s_line
{
	int x0;
	int y0;
	int	x1;
	int	y1;
	int	color;
}			t_line;