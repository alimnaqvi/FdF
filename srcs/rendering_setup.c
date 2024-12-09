/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering_setup.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaqvi <anaqvi@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 10:41:44 by anaqvi            #+#    #+#             */
/*   Updated: 2024/12/09 13:48:33 by anaqvi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_init_mlx(t_main *main)
{
	if (!main->mlx)
		main->mlx = mlx_init(WIDTH, HEIGHT, "FdF", true);
	if (!(main->mlx))
	{
		ft_putendl_fd(mlx_strerror(mlx_errno), STDERR_FILENO);
		ft_exit(main->allocs, EXIT_FAILURE);
	}
	if (main->img)
	{
		mlx_delete_image(main->mlx, main->img);
		main->img = NULL;
	}
	if (!main->img)
		main->img = mlx_new_image(main->mlx, WIDTH, HEIGHT);
	if (!(main->img))
	{
		ft_putendl_fd(mlx_strerror(mlx_errno), STDERR_FILENO);
		mlx_close_window(main->mlx);
		ft_exit(main->allocs, EXIT_FAILURE);
	}
	if (mlx_image_to_window(main->mlx, main->img, 0, 0) == -1)
	{
		ft_putendl_fd(mlx_strerror(mlx_errno), STDERR_FILENO);
		mlx_close_window(main->mlx);
		ft_exit(main->allocs, EXIT_FAILURE);
	}
}

static void set_map_defaults(t_map *map)
{
	uint32_t max_dimension;

	// Determine the maximum dimension of the map
	if (map->width > map->height)
		max_dimension = map->width;
	else
		max_dimension = map->height;
	// Compute scale to fit the map within the screen
	map->zoom = (WIDTH / 2) / (float)max_dimension;

	// Center the map on the screen
	map->x_offset = WIDTH * 0.4;
	map->y_offset = HEIGHT * 0.28;

	map->angle_x = PI / 30;
	map->angle_y = PI / -30;
	map->angle_z = PI / 6;
	map->scale_z = 0.2;
	map->proj_type = ISOMETRIC;
}

void	rendering_start(t_map *map, t_list **allocs)
{
	t_main		main;

	main.mlx = NULL;
	main.img = NULL;
	main.allocs = allocs;
	main.map = map;
	set_map_defaults(main.map);
	ft_init_mlx(&main);
	draw_map(&main);
	mlx_loop_hook(main.mlx, ft_hook, &main);
	mlx_scroll_hook(main.mlx, ft_zoom, &main);
	// mlx_loop_hook(main.mlx, draw_map, &main);
	mlx_loop(main.mlx);
	mlx_terminate(main.mlx);
}
