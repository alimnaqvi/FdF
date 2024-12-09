/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaqvi <anaqvi@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 12:04:17 by anaqvi            #+#    #+#             */
/*   Updated: 2024/12/09 18:39:43 by anaqvi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <math.h>
# include <fcntl.h>
# include <stdio.h>
# include <limits.h>
# include "ft_printf.h"
# include "get_next_line.h"
# include "libft.h"
# include "MLX42/MLX42.h"

# define WIDTH 		1280
# define HEIGHT 	720
# define PI		3.14159f

typedef enum e_projection_type {
       ISOMETRIC,
       SIDE_VIEW,
       TOP_DOWN,
   } t_proj_type;

typedef enum e_feature {
       OFFSET,
	   ANGLE,
	   ZOOM,
       SCALE_Z,
	   PROJ_TYPE,
	   COLOR,
	   RESET,
   } t_feature;

typedef enum e_color {
	INPUT,
	BONUS,
} t_color_tag;

typedef struct s_2d_point {
    int x;
    int y;
	uint32_t color;
} t_2d_point;

typedef struct s_3d_point {
    int x;
    int y;
    int z;
	uint32_t in_color;
	uint32_t bns_color;
} t_3d_point;

typedef struct s_map {
    t_3d_point 	**points;
    uint32_t 	width;
    uint32_t 	height;
	int			min_z;
	int			max_z;
	float		zoom;
	float		x_offset;
	float		y_offset;
	float		angle_x;
	float		angle_y;
	float		angle_z;
	float		scale_z;
	t_proj_type	proj_type;
	t_color_tag color_tag;
} t_map;

typedef struct s_main {
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_map	*map;
	t_list		**allocs;
} t_main;

typedef struct s_dda {
	float dx;
	float dy;
	int steps;
	float x_inc;
	float y_inc;
	float current_x;
	float current_y;
	int i;
	float percentage;
	uint32_t color;
} t_dda;

typedef struct s_color {
	uint8_t red;
	uint8_t green;
	uint8_t blue;
	uint8_t alpha;
} t_color;

// parse
t_map	*init_parse_file(int argc, char **argv, t_list **allocs);

// render setup
void	rendering_start(t_map *map, t_list **allocs);
void	ft_init_mlx(t_main *main);
void	set_map_defaults(t_map *map);

// hooks
void ft_hook1(void* param);
void ft_hook2(void* param);
void ft_zoom(double xdelta, double ydelta, void* param);

// draw
void	draw_map(t_main *main);

// memory
void	free_check_null(void *ptr);
void *ft_malloc(size_t size, t_list **allocs);
char *GNL_record_malloc(int fd, t_list **allocs);

// split
char	**ft_split_safe(char const *s, char c, t_list **allocs);

// trim
char	*ft_strtrim_safe(char const *s1, char const *set, t_list **allocs);

// utils
void ft_exit(t_list **allocs, int status);
uint32_t get_number_of_lines(char *file, t_list **allocs);
uint32_t	ft_atoi_color(char *str);

#endif
