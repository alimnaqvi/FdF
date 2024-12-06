/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaqvi <anaqvi@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 10:41:44 by anaqvi            #+#    #+#             */
/*   Updated: 2024/12/06 20:22:56 by anaqvi           ###   ########.fr       */
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

static void ft_hook(void* param)
{
	t_main *main = (t_main *)param;

	if (mlx_is_key_down(main->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(main->mlx);
}

void	rendering(t_3d_map *map, t_list **allocs)
{
	t_main		main;

	main.allocs = allocs;
	main.map = map;
	ft_init_mlx(&main);
	draw_map(&main);
	mlx_loop_hook(main.mlx, ft_hook, &main);
	mlx_loop(main.mlx);
	mlx_terminate(main.mlx);
}
