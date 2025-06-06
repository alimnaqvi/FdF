/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaqvi <anaqvi@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 18:51:53 by anaqvi            #+#    #+#             */
/*   Updated: 2024/12/09 19:56:39 by anaqvi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static t_2d_point	project_point(t_3d_point point, t_map *map)
{
	t_2d_point		projected;
	t_float_point	temp;

	temp.y = point.y * cos(map->angle_x) - point.z * sin(map->angle_x);
	temp.z = point.y * sin(map->angle_x) + point.z * cos(map->angle_x);
	temp.x = point.x * cos(map->angle_y) + temp.z * sin(map->angle_y);
	temp.z = -point.x * sin(map->angle_y) + temp.z * cos(map->angle_y);
	if (map->proj_type == ISOMETRIC || map->proj_type == SIDE_VIEW)
	{
		projected.x = (temp.x - temp.y) * cos(map->angle_z) * map->zoom;
		projected.y = ((temp.x + temp.y) * sin(map->angle_z) - temp.z
				* map->scale_z) * map->zoom;
	}
	else if (map->proj_type == TOP_DOWN)
	{
		projected.x = temp.x * map->zoom;
		projected.y = temp.y * map->zoom;
	}
	projected.x += map->x_offset;
	projected.y += map->y_offset;
	if (map->color_tag == INPUT)
		projected.color = point.in_color;
	else if (map->color_tag == BONUS)
		projected.color = point.bns_color;
	return (projected);
}

static uint32_t	interpolate_color(uint32_t start_color, uint32_t end_color,
		float percentage)
{
	t_color	start;
	t_color	end;
	t_color	result;

	start.red = (start_color >> 24) & 0xFF;
	start.green = (start_color >> 16) & 0xFF;
	start.blue = (start_color >> 8) & 0xFF;
	start.alpha = start_color & 0xFF;
	end.red = (end_color >> 24) & 0xFF;
	end.green = (end_color >> 16) & 0xFF;
	end.blue = (end_color >> 8) & 0xFF;
	end.alpha = end_color & 0xFF;
	result.red = start.red + percentage * (end.red - start.red);
	result.green = start.green + percentage * (end.green - start.green);
	result.blue = start.blue + percentage * (end.blue - start.blue);
	result.alpha = start.alpha + percentage * (end.alpha - start.alpha);
	return ((result.red << 24) | (result.green << 16)
		| (result.blue << 8) | result.alpha);
}

static void	draw_line(t_main *main, t_2d_point start, t_2d_point end)
{
	t_dda	dda;

	dda.dx = end.x - start.x;
	dda.dy = end.y - start.y;
	if (fabsf(dda.dx) > fabsf(dda.dy))
		dda.steps = fabsf(dda.dx);
	else
		dda.steps = fabsf(dda.dy);
	dda.x_inc = dda.dx / dda.steps;
	dda.y_inc = dda.dy / dda.steps;
	dda.current_x = start.x;
	dda.current_y = start.y;
	dda.i = 0;
	while (dda.i <= dda.steps)
	{
		dda.percentage = (float)dda.i++ / (float)dda.steps;
		dda.color = interpolate_color(start.color, end.color, dda.percentage);
		if (dda.current_x >= 0 && dda.current_y >= 0 && dda.current_x < WIDTH
			&& dda.current_y < HEIGHT)
			mlx_put_pixel(main->img, (int)dda.current_x, (int)dda.current_y,
				dda.color);
		dda.current_x += dda.x_inc;
		dda.current_y += dda.y_inc;
	}
}

static void	assign_bonus_color(uint32_t x, uint32_t y, t_main *main)
{
	if (abs(main->map->max_z))
		main->map->points[y][x].bns_color = interpolate_color(0x00A5B4D9,
				0xFF4D09D9, (float)abs(main->map->points[y][x].z)
				/ (float)abs(main->map->max_z));
}

void	draw_map(t_main *main)
{
	uint32_t	x;
	uint32_t	y;

	y = 0;
	while (y < main->map->height)
	{
		x = 0;
		while (x < main->map->width)
		{
			assign_bonus_color(x, y, main);
			if (x + 1 < main->map->width)
				draw_line(main, project_point(main->map->points[y][x],
						main->map), project_point(main->map->points[y][x + 1],
						main->map));
			if (y + 1 < main->map->height)
				draw_line(main, project_point(main->map->points[y][x],
						main->map), project_point(main->map->points[y + 1][x],
						main->map));
			x++;
		}
		y++;
	}
}
