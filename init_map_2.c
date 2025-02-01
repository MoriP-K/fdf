/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoriyam <kmoriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 22:24:28 by kmoriyam          #+#    #+#             */
/*   Updated: 2025/02/01 22:24:44 by kmoriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	count_word(const char *str, char delimeter)
{
	size_t	i;
	size_t	word_count;
	int		in_word;

	if (!str)
		return (0);
	i = 0;
	word_count = 0;
	in_word = 0;
	while (str[i])
	{
		if (str[i] != delimeter && str[i] != '\n')
		{
			if (in_word == 0)
			{
				in_word = 1;
				word_count++;
			}
		}
		else
			in_word = 0;
		i++;
	}
	return (word_count);
}

int	clean_up_width(int *check)
{
	int	width;

	width = check[0];
	free(check);
	return (width);
}
