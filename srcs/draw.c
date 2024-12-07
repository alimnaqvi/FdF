/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaqvi <anaqvi@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 18:51:53 by anaqvi            #+#    #+#             */
/*   Updated: 2024/12/07 18:50:56 by anaqvi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static t_2d_point isometric_projection(t_3d_point point, float angle, float scale_z, t_offsets offsets)
{
	t_2d_point projected;

	// Apply isometric transformation
	projected.x = (point.x - point.y) * cos(angle) * offsets.scale;
	projected.y = ((point.x + point.y) * sin(angle) - point.z * scale_z) * offsets.scale;

	// Center it on the window
	projected.x += offsets.x_offset;
	projected.y += offsets.y_offset;

	projected.color = point.color;

	return (projected);
}

// Interpolates between start_color and end_color based on "percentage" (0.0 to 1.0)
static uint32_t interpolate_color(uint32_t start_color, uint32_t end_color, float percentage)
{
	// Extract RGBA components from the start and end colors
	uint8_t sr = (start_color >> 24) & 0xFF; // Red component of start color
	uint8_t sg = (start_color >> 16) & 0xFF; // Green component of start color
	uint8_t sb = (start_color >> 8) & 0xFF;  // Blue component of start color
	uint8_t sa = start_color & 0xFF;         // Alpha component of start color

	uint8_t er = (end_color >> 24) & 0xFF;   // Red component of end color
	uint8_t eg = (end_color >> 16) & 0xFF;   // Green component of end color
	uint8_t eb = (end_color >> 8) & 0xFF;    // Blue component of end color
	uint8_t ea = end_color & 0xFF;           // Alpha component of end color

	// Interpolate each component
	uint8_t r = sr + percentage * (er - sr);
	uint8_t g = sg + percentage * (eg - sg);
	uint8_t b = sb + percentage * (eb - sb);
	uint8_t a = sa + percentage * (ea - sa);

	// Combine the interpolated RGBA components back into a single integer
	return ((r << 24) | (g << 16) | (b << 8) | a);
}

static void draw_line(t_main *main, t_2d_point start, t_2d_point end)
{
	int dx = abs((int)end.x - (int)start.x);
	int dy = abs((int)end.y - (int)start.y);
	int sx = (start.x < end.x) ? 1 : -1;
	int sy = (start.y < end.y) ? 1 : -1;
	int err = dx - dy;
	int e2;
	int steps = dx > dy ? dx : dy;  // Find the total number of steps (longer axis)
	int current_step = 0;

	// Ensure the line stays within bounds while drawing
	while ((int)start.x != (int)end.x || (int)start.y != (int)end.y)
	{
		// Calculate the percentage of completion along the line
		float percentage = (float)current_step / (float)steps;

		// Interpolate color based on percentage
		uint32_t color = interpolate_color(start.color, end.color, percentage);

		// Draw the pixel if within bounds
		if (start.x >= 0 && start.y >= 0 && start.x < WIDTH && start.y < HEIGHT)
			mlx_put_pixel(main->img, (int)start.x, (int)start.y, color);

		// Update Bresenham's error terms
		e2 = 2 * err;
		if (e2 > -dy)
		{
			err -= dy;
			start.x += sx;
		}
		if (e2 < dx)
		{
			err += dx;
			start.y += sy;
		}

		// Increment the step counter
		current_step++;
	}

	// Draw the last pixel (with the end color)
	if (end.x >= 0 && end.y >= 0 && end.x < WIDTH && end.y < HEIGHT)
		mlx_put_pixel(main->img, (int)end.x, (int)end.y, end.color);
}

void draw_map(t_main *main)
{
	uint32_t	x;
	uint32_t    y;

	y = 0;
	while (y < main->map->height)
	{
		x = 0;
		while (x < main->map->width)
		{
			// Draw horizontal lines
			if (x + 1 < main->map->width)
				draw_line(main, 
					isometric_projection(main->map->points[y][x], main->map->angle, main->map->scale_z, main->map->offsets),
					isometric_projection(main->map->points[y][x + 1], main->map->angle, main->map->scale_z, main->map->offsets));
			// Draw vertical lines
			if (y + 1 < main->map->height)
				draw_line(main, 
					isometric_projection(main->map->points[y][x], main->map->angle, main->map->scale_z, main->map->offsets),
					isometric_projection(main->map->points[y + 1][x], main->map->angle, main->map->scale_z, main->map->offsets));
			x++;
		}
		y++;
	}
}
