/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaqvi <anaqvi@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 18:37:58 by anaqvi            #+#    #+#             */
/*   Updated: 2024/12/05 18:15:11 by anaqvi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	open_file(int argc, char **argv)
{
	int	fd;

	if (argc != 2)
	{
		ft_putendl_fd("Usage: ./fdf <path to .fdf file>", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		perror(argv[1]);
		exit(EXIT_FAILURE);
	}
	return (fd);
}

static uint32_t get_number_of_lines(int fd)
{
	uint32_t i;
	char *line;
	
	i = 0;
	line = get_next_line(fd);
	while(line)
	{
		i++;
		free(line);
		line = get_next_line(fd);
	}
	return (i);
}

t_3d_map	*init_parse_file(int argc, char **argv, t_list **allocs)
{
	int	fd;
	uint32_t	x;
	uint32_t y;
	char *line;
	char **in_points;
	t_3d_map *map;

	fd = open_file(argc, argv);
	map = ft_malloc(sizeof(t_3d_map), allocs);
	map->height = get_number_of_lines(fd);
	map->points = ft_malloc(sizeof(t_3d_point *) * map->height, allocs);
	y = 0;
	line = get_next_line(fd);
	while (line)
	{
		in_points = ft_split_ft_malloc(line, ' ', allocs);
		map->width = 0;
		while (in_points[map->width])
			(map->width)++;
		map->points[y] = ft_malloc(sizeof(t_3d_point) * map->width, allocs);
		x = 0;
		while (*in_points)
		{
			// ft_printf("row %u column %u: ", y, x);
			map->points[y][x].x = x;
			map->points[y][x].y = y;
			map->points[y][x].z = ft_atoi(*in_points);
			// ft_printf("value of z is: %u\n", map->points[y][x].z);
			// map->points[y][x].color = get_color(*in_points);
			in_points++;
			x++;
		}
		free(line);
		line = get_next_line(fd);
		y++;
	}
	// check if width is constant
	close(fd);
	return (map);
}
