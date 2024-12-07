/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaqvi <anaqvi@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 10:41:44 by anaqvi            #+#    #+#             */
/*   Updated: 2024/12/07 21:30:15 by anaqvi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	ft_init_mlx(t_main *main)
{
	main->mlx = mlx_init(WIDTH, HEIGHT, "FdF", true);
	if (!(main->mlx))
	{
		ft_putendl_fd(mlx_strerror(mlx_errno), STDERR_FILENO);
		ft_exit(main->allocs, EXIT_FAILURE);
	}
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
	max_dimension = map->width > map->height ? map->width : map->height;

	// Compute scale to fit the map within the screen
	map->zoom = (WIDTH / 2) / (float)max_dimension;

	// Center the map on the screen
	map->x_offset = WIDTH * 0.4;
	map->y_offset = HEIGHT * 0.28;

	map->angle_y = PI / -30;
	map->angle_x = PI / 30;
	map->scale_z = 0.2;
}

static void reset_draw_new(t_main *main, char *var, char axis, float value)
{
	mlx_image_t *to_delete;

	if (var == 'o')
	{
		if (axis == 'x')
			main->map->x_offset += value;
		else if (axis == 'y')
			main->map->y_offset += value;
	}
	else if (var == 's')
		main->map->zoom += value;
	else if (var == 'a')
	{
		if (axis == 'x')
			main->map->angle_x += value;
		else if (axis == 'y')
			main->map->angle_y += value;
	}
	else if (var == 'z')
		main->map->scale_z += value;
	// printf("map->angle_x is now: %.2f\n", PI / (main->map->angle_x));
	// printf("map->angle_y is now: %.2f\n", PI / (main->map->angle_y));
	to_delete = main->img;
	main->img = mlx_new_image(main->mlx, WIDTH, HEIGHT); // need to check for error
	mlx_image_to_window(main->mlx, main->img, 0, 0); // need to check for error
	draw_map(main);
	mlx_delete_image(main->mlx, to_delete);
}

static void ft_hook(void* param)
{
	t_main *main = (t_main *)param;

	if (mlx_is_key_down(main->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(main->mlx);
	else if (mlx_is_key_down(main->mlx, MLX_KEY_LEFT_CONTROL) && mlx_is_key_down(main->mlx, MLX_KEY_UP))
		reset_draw_new(main, 'z', 'z', 0.01);
	else if (mlx_is_key_down(main->mlx, MLX_KEY_LEFT_CONTROL) && mlx_is_key_down(main->mlx, MLX_KEY_DOWN))
		reset_draw_new(main, 'z', 'z', -0.01);
	else if (mlx_is_key_down(main->mlx, MLX_KEY_UP))
		reset_draw_new(main, 'o', 'y', -2);
	else if (mlx_is_key_down(main->mlx, MLX_KEY_DOWN))
		reset_draw_new(main, 'o', 'y', 2);
	else if (mlx_is_key_down(main->mlx, MLX_KEY_LEFT))
		reset_draw_new(main, 'o', 'x', -2);
	else if (mlx_is_key_down(main->mlx, MLX_KEY_RIGHT))
		reset_draw_new(main, 'o', 'x', 2);
	else if (mlx_is_key_down(main->mlx, MLX_KEY_W))
		reset_draw_new(main, 'a', 'y', -0.005);
	else if (mlx_is_key_down(main->mlx, MLX_KEY_S))
		reset_draw_new(main, 'a', 'y', 0.005);
	else if (mlx_is_key_down(main->mlx, MLX_KEY_A))
		reset_draw_new(main, 'a', 'x', -0.005);
	else if (mlx_is_key_down(main->mlx, MLX_KEY_D))
		reset_draw_new(main, 'a', 'x', 0.005);
}

static void zoom(double xdelta, double ydelta, void* param)
{
	t_main *main = (t_main *)param;

	if (ydelta > 0)
		reset_draw_new(main, 's', 'y', 2);
	else if (ydelta < 0)
		reset_draw_new(main, 's', 'y', -2);
}

void	rendering(t_map *map, t_list **allocs)
{
	t_main		main;

	main.allocs = allocs;
	main.map = map;
	set_map_defaults(main.map);
	ft_init_mlx(&main);
	draw_map(&main);
	mlx_loop_hook(main.mlx, ft_hook, &main);
	mlx_scroll_hook(main.mlx, zoom, &main);
	// mlx_loop_hook(main.mlx, draw_map, &main);
	mlx_loop(main.mlx);
	mlx_terminate(main.mlx);
}
