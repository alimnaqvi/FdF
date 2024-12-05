/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaqvi <anaqvi@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 18:36:04 by anaqvi            #+#    #+#             */
/*   Updated: 2024/12/05 17:11:29 by anaqvi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void ft_exit(t_list **allocs, int status)
{
	ft_lstclear(allocs, free_check_null);
	exit(status);
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
