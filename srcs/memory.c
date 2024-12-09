/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaqvi <anaqvi@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 15:49:27 by anaqvi            #+#    #+#             */
/*   Updated: 2024/12/09 18:31:55 by anaqvi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	free_and_null(void **ptr)
{
	if (*ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
}

void	free_check_null(void *ptr)
{
	if (ptr)
		free(ptr);
}

void *ft_malloc(size_t size, t_list **allocs)
{
	void	*ptr;
	t_list	*alloc_node;

	ptr = malloc(size);
	if (!ptr)
	{
		ft_putendl_fd("malloc failed", STDERR_FILENO);
		ft_lstclear(allocs, free_check_null);
		exit(EXIT_FAILURE);
	}
	alloc_node = ft_lstnew(ptr);
	if (!alloc_node)
	{
		ft_putendl_fd("malloc failed", STDERR_FILENO);
		ft_lstclear(allocs, free_check_null);
		exit(EXIT_FAILURE);
	}
	ft_lstadd_front(allocs, alloc_node);
	return (ptr);
}

char *GNL_record_malloc(int fd, t_list **allocs)
{
	char *line;
	t_list	*alloc_node;

	line = get_next_line(fd);
	alloc_node = ft_lstnew((void *)line);
	if (!alloc_node)
	{
		ft_putendl_fd("malloc failed", STDERR_FILENO);
		ft_lstclear(allocs, free_check_null);
		exit(EXIT_FAILURE);
	}
	ft_lstadd_front(allocs, alloc_node);
	return (line);
}
