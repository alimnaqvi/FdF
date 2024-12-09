/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaqvi <anaqvi@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 12:40:41 by anaqvi            #+#    #+#             */
/*   Updated: 2024/12/09 14:00:14 by anaqvi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void reset_draw_new(t_main *main, t_feature var, char axis, float value)
{
	if (var == OFFSET)
	{
		if (axis == 'x')
			main->map->x_offset += value;
		else if (axis == 'y')
			main->map->y_offset += value;
	}
	else if (var == ZOOM)
		main->map->zoom += value;
	else if (var == ANGLE)
	{
		if (axis == 'x')
			main->map->angle_x += value;
		else if (axis == 'y')
			main->map->angle_y += value;
		else if (axis == 'z')
			main->map->angle_z += value;
	}
	else if (var == SCALE_Z)
		main->map->scale_z += value;
	else if (var == PROJ_TYPE)
	{
		if (main->map->proj_type == SIDE_VIEW)
			main->map->angle_z = 0;
		main->map->proj_type = value;
	}
	ft_init_mlx(main);
	draw_map(main);
}

void ft_hook(void* param)
{
	t_main *main = (t_main *)param;

	if (mlx_is_key_down(main->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(main->mlx);
	else if (mlx_is_key_down(main->mlx, MLX_KEY_LEFT_CONTROL) && mlx_is_key_down(main->mlx, MLX_KEY_UP))
		reset_draw_new(main, SCALE_Z, 'z', 0.01);
	else if (mlx_is_key_down(main->mlx, MLX_KEY_LEFT_CONTROL) && mlx_is_key_down(main->mlx, MLX_KEY_DOWN))
		reset_draw_new(main, SCALE_Z, 'z', -0.01);
	else if (mlx_is_key_down(main->mlx, MLX_KEY_UP))
		reset_draw_new(main, OFFSET, 'y', -2);
	else if (mlx_is_key_down(main->mlx, MLX_KEY_DOWN))
		reset_draw_new(main, OFFSET, 'y', 2);
	else if (mlx_is_key_down(main->mlx, MLX_KEY_LEFT))
		reset_draw_new(main, OFFSET, 'x', -2);
	else if (mlx_is_key_down(main->mlx, MLX_KEY_RIGHT))
		reset_draw_new(main, OFFSET, 'x', 2);
	else if (mlx_is_key_down(main->mlx, MLX_KEY_A))
		reset_draw_new(main, ANGLE, 'y', -0.005);
	else if (mlx_is_key_down(main->mlx, MLX_KEY_D))
		reset_draw_new(main, ANGLE, 'y', 0.005);
	else if (mlx_is_key_down(main->mlx, MLX_KEY_Q))
		reset_draw_new(main, ANGLE, 'x', -0.005);
	else if (mlx_is_key_down(main->mlx, MLX_KEY_E))
		reset_draw_new(main, ANGLE, 'x', 0.005);
	else if (mlx_is_key_down(main->mlx, MLX_KEY_W))
		reset_draw_new(main, ANGLE, 'z', -0.005);
	else if (mlx_is_key_down(main->mlx, MLX_KEY_S))
		reset_draw_new(main, ANGLE, 'z', 0.005);
	else if (mlx_is_key_down(main->mlx, MLX_KEY_1))
		reset_draw_new(main, PROJ_TYPE, 0, ISOMETRIC);
	else if (mlx_is_key_down(main->mlx, MLX_KEY_2))
		reset_draw_new(main, PROJ_TYPE, 0, SIDE_VIEW);
	else if (mlx_is_key_down(main->mlx, MLX_KEY_3))
		reset_draw_new(main, PROJ_TYPE, 0, TOP_DOWN);
}

void ft_zoom(double xdelta, double ydelta, void* param)
{
	t_main *main = (t_main *)param;

	if (ydelta > 0)
		reset_draw_new(main, ZOOM, 0, 2);
	else if (ydelta < 0)
		reset_draw_new(main, ZOOM, 0, -2);
}
