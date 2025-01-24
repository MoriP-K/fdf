/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoriyam <kmoriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 15:00:59 by kmoriyam          #+#    #+#             */
/*   Updated: 2025/01/22 21:08:28 by kmoriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	read_fd(t_sp *p, char **line, int fd)
{
	if (p->buf_pos >= p->bytes_read)
	{
		p->bytes_read = read(fd, p->buf, BUFFER_SIZE);
		if (p->bytes_read <= 0)
		{
			if (p->line_pos == 0 || p->bytes_read < 0)
			{
				free(*line);
				*line = NULL;
				return (0);
			}
			(*line)[p->line_pos] = '\0';
			return (-1);
		}
		p->buf_pos = 0;
	}
	return (1);
}

int	add_buf(t_sp *p, char **line, char *new_line)
{
	if (p->line_pos >= BUFFER_SIZE)
	{
		new_line = (char *)malloc(p->line_pos + BUFFER_SIZE + 1);
		if (!new_line)
		{
			free(*line);
			return (0);
		}
		ft_memcpy(new_line, *line, p->line_pos);
		free(*line);
		*line = new_line;
	}
	return (1);
}

void	init_all(t_sp *p, char **new_line)
{
	if (p->bytes_read == 0)
	{
		p->buf_pos = 0;
		p->bytes_read = 0;
	}
	p->line_pos = 0;
	p->ret = 0;
	*new_line = NULL;
}

char	*get_next_line(int fd)
{
	static t_sp	p;
	char		*line;
	char		*new_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = (char *)malloc(BUFFER_SIZE + 1);
	if (!line)
		return (NULL);
	init_all(&p, &new_line);
	while (1)
	{
		p.ret = read_fd(&p, &line, fd);
		if (p.ret == -1)
			return (line);
		else if (p.ret == 0)
			return (NULL);
		line[p.line_pos++] = p.buf[p.buf_pos++];
		if (!add_buf(&p, &line, new_line))
			return (NULL);
		if (line[p.line_pos - 1] == '\n')
			break ;
	}
	line[p.line_pos] = '\0';
	return (line);
}

// #include <fcntl.h>
// #include <stdio.h>

// int	main(int ac, char **av)
// {
// 	int		fd;
// 	char	*s;
// 	int		count;

// 	if (ac != 2)
// 		return (1);
// 	fd = open(av[1], O_RDONLY);
// 	if (fd == -1)
// 		return (1);
// 	count = 0;
// 	while (1)
// 	{
// 		s = get_next_line(fd);
// 		if (!s)
// 		{
// 			break ;
// 		}
// 		printf("%s", s);
// 		count++;
// 		free(s);
// 	}
// 	printf("\n\ncount = %d\n", count);
// 	close(fd);
// }
