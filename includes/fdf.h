/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaqvi <anaqvi@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 12:04:17 by anaqvi            #+#    #+#             */
/*   Updated: 2024/12/05 18:04:03 by anaqvi           ###   ########.fr       */
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
	uint32_t color;
} t_3d_point;

// Store all points in a 2-dimensional array (each inside array is one horizontal line of points)
typedef struct s_3d_map {
    t_3d_point **points;  // 2D array of points
    uint32_t width;         // Number of columns (x-coordinates)
    uint32_t height;        // Number of rows (y-coordinates)
} t_3d_map;

typedef struct s_2d_point {
    int x;
    int y;
	uint32_t color;
} t_2d_point;

typedef struct s_2d_map {
    t_2d_point **points;  // 2D array of points
    uint32_t width;         // Number of columns (x-coordinates)
    uint32_t height;        // Number of rows (y-coordinates)
	int angle;
	int scale_z;
} t_2d_map;

// parse
t_3d_map	*init_parse_file(int argc, char **argv, t_list **allocs);

// memory
void	free_check_null(void *ptr);
void *ft_malloc(size_t size, t_list **allocs);

// split
char	**ft_split_ft_malloc(char const *s, char c, t_list **allocs);

// utils
void ft_exit(t_list **allocs, int status);

#endif
