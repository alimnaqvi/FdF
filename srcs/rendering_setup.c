/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering_setup.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaqvi <anaqvi@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 10:41:44 by anaqvi            #+#    #+#             */
/*   Updated: 2024/12/09 19:38:57 by anaqvi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_init_mlx(t_main *main)
{
	if (!main->mlx)
		main->mlx = mlx_init(WIDTH, HEIGHT, "FdF", true);
	if (!(main->mlx))
		return (ft_putendl_fd((char *)mlx_strerror(mlx_errno), STDERR_FILENO),
			ft_exit(main->allocs, EXIT_FAILURE));
	if (main->img)
	{
		mlx_delete_image(main->mlx, main->img);
		main->img = NULL;
	}
	if (!main->img)
		main->img = mlx_new_image(main->mlx, WIDTH, HEIGHT);
	if (!(main->img))
	{
		ft_putendl_fd((char *)mlx_strerror(mlx_errno), STDERR_FILENO);
		mlx_close_window(main->mlx);
		ft_exit(main->allocs, EXIT_FAILURE);
	}
	if (mlx_image_to_window(main->mlx, main->img, 0, 0) == -1)
	{
		ft_putendl_fd((char *)mlx_strerror(mlx_errno), STDERR_FILENO);
		mlx_close_window(main->mlx);
		ft_exit(main->allocs, EXIT_FAILURE);
	}
}

void	set_map_defaults(t_map *map)
{
	uint32_t	max_dimension;

	if (map->width > map->height)
		max_dimension = map->width;
	else
		max_dimension = map->height;
	map->zoom = (WIDTH / 2) / (float)max_dimension;
	map->x_offset = WIDTH * 0.4;
	map->y_offset = HEIGHT * 0.28;
	map->angle_x = PI / 30;
	map->angle_y = PI / -30;
	map->angle_z = PI / 6;
	map->scale_z = 0.2;
	map->proj_type = ISOMETRIC;
	map->color_tag = INPUT;
}

static void	show_menu(mlx_t *mlx)
{
	int32_t	x;
	int32_t	y;

	x = 20;
	y = 20;
	mlx_put_string(mlx, "ACTION\t\t\t\t\t\t\t\tKEY", x, y);
	mlx_put_string(mlx, "Color\t\t\t\t\t\t\t\t\tc", x, y += 35);
	mlx_put_string(mlx, "Zoom\t\t\t\t\t\t\t\t\t\tMouse scroll", x, y += 20);
	mlx_put_string(mlx, "Move\t\t\t\t\t\t\t\t\t\tArrow keys", x, y += 20);
	mlx_put_string(mlx, "Scale z\t\t\t\t\t\t\tctrl + up/down arrow key", x, y
		+= 20);
	mlx_put_string(mlx, "Rotate\t\t\t\t\t\t\t\tw/a/s/d/q/e", x, y += 20);
	mlx_put_string(mlx, "CHANGE VIEW/PROJECTION:", x, y += 30);
	mlx_put_string(mlx, "Isometric\t\t\t\t\t1", x, y += 20);
	mlx_put_string(mlx, "Side view\t\t\t\t\t2", x, y += 20);
	mlx_put_string(mlx, "Top down view\t3", x, y += 20);
	mlx_put_string(mlx, "Reset\t\t\t\t\t\t\t\t\tr", x, y += 30);
}

void	rendering_start(t_map *map, t_list **allocs)
{
	t_main	main;

	main.mlx = NULL;
	main.img = NULL;
	main.allocs = allocs;
	main.map = map;
	set_map_defaults(main.map);
	ft_init_mlx(&main);
	show_menu(main.mlx);
	draw_map(&main);
	mlx_loop_hook(main.mlx, ft_hook1, &main);
	mlx_loop_hook(main.mlx, ft_hook2, &main);
	mlx_scroll_hook(main.mlx, ft_zoom, &main);
	mlx_loop(main.mlx);
	mlx_terminate(main.mlx);
}
