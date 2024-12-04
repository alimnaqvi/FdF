/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaqvi <anaqvi@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 18:36:04 by anaqvi            #+#    #+#             */
/*   Updated: 2024/12/04 18:36:21 by anaqvi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	free_splits(char ***splits)
{
	int	i;

	if (!splits || !*splits)
		return ;
	i = 0;
	while ((*splits)[i])
	{
		free((*splits)[i]);
		i++;
	}
	free(*splits);
	*splits = NULL;
}
