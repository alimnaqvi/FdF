/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaqvi <anaqvi@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 18:38:01 by anaqvi            #+#    #+#             */
/*   Updated: 2024/12/09 18:54:12 by anaqvi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(int argc, char **argv)
{
	t_list	*allocs;
	t_map	*map_3d;

	allocs = NULL;
	map_3d = init_parse_file(argc, argv, &allocs);
	rendering_start(map_3d, &allocs);
	ft_exit(&allocs, EXIT_SUCCESS);
}
