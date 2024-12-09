/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaqvi <anaqvi@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 18:37:58 by anaqvi            #+#    #+#             */
/*   Updated: 2024/12/09 18:45:22 by anaqvi           ###   ########.fr       */
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

static uint32_t	get_color(char *str, t_list **allocs)
{
	char **splits;

	if (!ft_strchr(str, ','))
		return (0xFFFFFFFF);
	splits = ft_split_safe(str, ',', allocs);
	if (splits && splits[1])
		return(ft_atoi_color(splits[1]));
	return(0xFFFFFFFF);
}

// void allocate_map_points(uint32_t y, char *line, t_map *map, t_list **allocs)
// {
// 	uint32_t cur_width;
// 	char **in_points;
// 	uint32_t	x;

// 	in_points = ft_split_safe(ft_strtrim_safe(line, "\n", allocs), ' ', allocs);
// 	cur_width = 0;
// 	while (in_points[cur_width])
// 		(cur_width)++;
// 	if (y != 0 && cur_width != map->width)
// 	{
// 		ft_putendl_fd("Invalid map. Ensure uniform width.", STDERR_FILENO);
// 		close(fd);
// 		ft_exit(allocs, EXIT_FAILURE);
// 	}
// 	map->width = cur_width;
// 	map->points[y] = ft_malloc(sizeof(t_3d_point) * map->width, allocs);
// 	x = 0;
// 	while (*in_points)
// 	{
// 		map->points[y][x].x = x;
// 		map->points[y][x].y = y;
// 		map->points[y][x].z = ft_atoi(*in_points);
// 		map->points[y][x].in_color = get_color(*in_points, allocs);
// 		if (map->points[y][x].z > map->max_z)
// 			map->max_z = map->points[y][x].z;
// 		if (map->points[y][x].z < map->min_z)
// 			map->min_z = map->points[y][x].z;
// 		in_points++;
// 		x++;
// 	}
// }

t_map	*init_parse_file(int argc, char **argv, t_list **allocs)
{
	int	fd;
	uint32_t	x;
	uint32_t y;
	uint32_t cur_width;
	char *line;
	char **in_points;
	t_map *map;

	fd = open_file(argc, argv);
	map = ft_malloc(sizeof(t_map), allocs);
	map->height = get_number_of_lines(argv[1], allocs);
	map->points = ft_malloc(sizeof(t_3d_point *) * map->height, allocs);
	map->min_z = INT_MAX;
	map->max_z = INT_MIN;
	y = 0;
	line = GNL_record_malloc(fd, allocs);
	while (line)
	{
		in_points = ft_split_safe(ft_strtrim_safe(line, "\n", allocs), ' ', allocs);
		cur_width = 0;
		while (in_points[cur_width])
			(cur_width)++;
		if (y != 0 && cur_width != map->width)
		{
			ft_putendl_fd("Invalid map. Ensure uniform width.", STDERR_FILENO);
			close(fd);
			ft_exit(allocs, EXIT_FAILURE);
		}
		map->width = cur_width;
		map->points[y] = ft_malloc(sizeof(t_3d_point) * map->width, allocs);
		x = 0;
		while (*in_points)
		{
			map->points[y][x].x = x;
			map->points[y][x].y = y;
			map->points[y][x].z = ft_atoi(*in_points);
			map->points[y][x].in_color = get_color(*in_points, allocs);
			if (map->points[y][x].z > map->max_z)
				map->max_z = map->points[y][x].z;
			if (map->points[y][x].z < map->min_z)
				map->min_z = map->points[y][x].z;
			in_points++;
			x++;
		}
		line = GNL_record_malloc(fd, allocs);
		y++;
	}
	close(fd);
	return (map);
}
