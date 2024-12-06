/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaqvi <anaqvi@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 18:37:58 by anaqvi            #+#    #+#             */
/*   Updated: 2024/12/06 11:42:43 by anaqvi           ###   ########.fr       */
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

static uint32_t get_number_of_lines(char *file, t_list **allocs)
{
	int fd;
	uint32_t i;
	char *line;
	
	i = 0;
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		perror(file);
		ft_exit(allocs, EXIT_FAILURE);
	}
	line = get_next_line(fd);
	while(line)
	{
		i++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (i);
}

static uint32_t	ft_atoi_color(char *str)
{
	uint32_t	color;
	int			i;
	char		c;

	if (!str || str[0] != '0' || str[1] != 'x')
		return (0x000000FF);
	color = 0;
	i = 2;
	while (str[i])
	{
		c = str[i];
		if (c >= '0' && c <= '9')
			c = c - '0';
		else if (c >= 'a' && c <= 'f')
			c = c - 'a' + 10;
		else if (c >= 'A' && c <= 'F')
			c = c - 'A' + 10;
		else
			return (0x000000FF);
		color = (color << 4) | c;
		i++;
	}
	if (i == 2)
		return (0x000000FF);
	return ((color << 8) | 0xFF);
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

t_3d_map	*init_parse_file(int argc, char **argv, t_list **allocs)
{
	int	fd;
	uint32_t	x;
	uint32_t y;
	uint32_t cur_width;
	char *line;
	char **in_points;
	t_3d_map *map;

	fd = open_file(argc, argv);
	map = ft_malloc(sizeof(t_3d_map), allocs);
	map->height = get_number_of_lines(argv[1], allocs);
	map->points = ft_malloc(sizeof(t_3d_point *) * map->height, allocs);
	y = 0;
	line = get_next_line(fd);
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
			map->points[y][x].color = get_color(*in_points, allocs);
			in_points++;
			x++;
		}
		free(line);
		line = get_next_line(fd);
		y++;
	}
	close(fd);
	return (map);
}
