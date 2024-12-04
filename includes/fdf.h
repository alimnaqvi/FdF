/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaqvi <anaqvi@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 12:04:17 by anaqvi            #+#    #+#             */
/*   Updated: 2024/12/04 19:28:59 by anaqvi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <math.h>
# include <fcntl.h>
# include <stdio.h>
# include "ft_printf.h"
# include "get_next_line.h"
# include "libft.h"
# include "MLX42/MLX42.h"

// Represents a point in 3-dimensional space
typedef struct s_3d_point {
    int x;  // x-coordinate
    int y;  // y-coordinate
    int z;  // altitude (z-coordinate)
	unsigned int color;
} t_3d_point;

// Store all points in a 2-dimensional array (each inside array is one horizontal line of points)
typedef struct s_3d_map {
    t_3d_point **points;  // 2D array of points
    int width;         // Number of columns (x-coordinates)
    int height;        // Number of rows (y-coordinates)
} t_3d_map;

typedef struct s_2d_point {
    int x;
    int y;
	unsigned int color;
} t_2d_point;

typedef struct s_2d_map {
    t_2d_point **points;  // 2D array of points
    int width;         // Number of columns (x-coordinates)
    int height;        // Number of rows (y-coordinates)
	int angle;
	int scale_z;
} t_2d_map;

// parse


// utils
void	free_splits(char ***splits);

#endif
