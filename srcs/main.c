/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaqvi <anaqvi@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 18:38:01 by anaqvi            #+#    #+#             */
/*   Updated: 2024/12/07 21:30:15 by anaqvi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int main(int argc, char **argv)
{
	t_list *allocs;
	t_map	*map_3d;

	allocs = NULL;
	map_3d = init_parse_file(argc, argv, &allocs); // parses the .fdf files and saves the 3D points
	rendering(map_3d, &allocs);
	// map_2d = transform_map_to_2d(map_3d);
	// draw_map(map_2d);
	// test_print_map(*map_3d);
	ft_exit(&allocs, EXIT_SUCCESS);
}

// static void test_print_map(t_map map_3d)
// {
// 	int i = 0;
// 	int j;

// 	while (i < map_3d.height)
// 	{
// 		j = 0;
// 		while (j < map_3d.width)
// 		{
// 			ft_printf("(%u, %u, %u) ", map_3d.points[i][j].x, map_3d.points[i][j].y, map_3d.points[i][j].z);
// 			j++;
// 		}
// 		ft_printf("\n");
// 		i++;
// 	}
// }