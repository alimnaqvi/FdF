/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaqvi <anaqvi@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 18:36:04 by anaqvi            #+#    #+#             */
/*   Updated: 2024/12/09 18:39:33 by anaqvi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void ft_exit(t_list **allocs, int status)
{
	ft_lstclear(allocs, free_check_null);
	exit(status);
}

uint32_t get_number_of_lines(char *file, t_list **allocs)
{
	int fd;
	uint32_t i;
	char *line;
	
	i = 0;
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		perror(file);
		ft_exit(allocs, EXIT_FAILURE);
	}
	line = GNL_record_malloc(fd, allocs);
	while(line)
	{
		i++;
		line = GNL_record_malloc(fd, allocs);
	}
	close(fd);
	return (i);
}

uint32_t	ft_atoi_color(char *str)
{
	uint32_t	color;
	int			i;
	char		c;

	if (!str || str[0] != '0' || str[1] != 'x')
		return (0x000000FF);
	color = 0;
	i = 2;
	while (str[i])
	{
		c = str[i];
		if (c >= '0' && c <= '9')
			c = c - '0';
		else if (c >= 'a' && c <= 'f')
			c = c - 'a' + 10;
		else if (c >= 'A' && c <= 'F')
			c = c - 'A' + 10;
		else
			return (0x000000FF);
		color = (color << 4) | c;
		i++;
	}
	if (i == 2)
		return (0x000000FF);
	return ((color << 8) | 0xFF);
}

// void	free_splits(char ***splits)
// {
// 	int	i;

// 	if (!splits || !*splits)
// 		return ;
// 	i = 0;
// 	while ((*splits)[i])
// 	{
// 		free((*splits)[i]);
// 		i++;
// 	}
// 	free(*splits);
// 	*splits = NULL;
// }
