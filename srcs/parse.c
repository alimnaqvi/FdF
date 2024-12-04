/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaqvi <anaqvi@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 18:37:58 by anaqvi            #+#    #+#             */
/*   Updated: 2024/12/04 19:28:17 by anaqvi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_3d_map	parse_input_file(int argc, char **argv)
{
	int	fd;

	if (argc != 2)
	{
		ft_putendl_fd("Usage: ./fdf <path to .fdf file>", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		perror(argv[1]);
		exit(EXIT_FAILURE);
	}
	// 
	close(fd);
}
