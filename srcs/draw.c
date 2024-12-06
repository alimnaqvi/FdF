/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaqvi <anaqvi@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 18:51:53 by anaqvi            #+#    #+#             */
/*   Updated: 2024/12/06 20:25:11 by anaqvi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static t_2d_point isometric_projection(t_3d_point point, float angle, float scale_z)
{
	t_2d_point projected;

	float cos_theta = cos(angle);
    float sin_theta = sin(angle);

	projected.x = (point.x - point.y) * cos_theta;
    projected.y = (point.x + point.y) * sin_theta - point.z * scale_z;
    return (projected);
}

static void draw_line(t_main *main, t_2d_point point_1, t_2d_point point_2)
{
	float x1;
	float y1;
	uint32_t dx;
	uint32_t dy;
	uint32_t steps;
	uint32_t i;
	float xinc;
	float yinc;
	
	dx = abs(point_2.x - point_1.x);
	dy = abs(point_2.y - point_1.y);
	if (dx > dy)
		 steps = dx;
	else
		steps = dy;
	xinc = (float)dx / (float)steps;
	yinc = (float)dy / (float)steps;
	
	i = 0;
	while (i <= steps)
	{
		if (point_1.x < main->map->width && point_1.y < main->map->height)
		{
			mlx_put_pixel(main->img, point_1.x, point_1.y, 0xFFFFFFFF);
			ft_printf("putting pixel at: (%i, %i)\n", point_1.x, point_1.y);
		}
		point_1.x = (uint32_t)roundf((float)point_1.x + xinc);
		point_1.y = (uint32_t)roundf((float)point_1.y + yinc);
		i++;
	}
}

void	draw_map(t_main *main)
{
	uint32_t	x;
	uint32_t 	y;

	y = 0;
	while (y < main->map->height)
	{
		x = 0;
		while (x < main->map->width)
		{
			if (x + 1 < main->map->width)
				draw_line(main, isometric_projection(main->map->points[y][x], PI/6, 1),
					isometric_projection(main->map->points[y][x + 1], PI/6, 1));
			if (y + 1 < main->map->height)
				draw_line(main, isometric_projection(main->map->points[y][x], PI / 6, 1),
					isometric_projection(main->map->points[y + 1][x], PI / 6, 1));
			x++;
		}
		y++;
	}
}
