/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngcki <youngcki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 19:31:40 by youngcki          #+#    #+#             */
/*   Updated: 2024/07/04 20:31:01 by youngcki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	free_data(t_shared *data)
{
	if (data->philo != 0)
		free(data->philo);
	return (0);
}

void	all_join(t_shared *data)
{
	int	i;

	i = 0;
	while (i < data->philo_num)
	{
		pthread_join(data->philo[i], 0);
		i++;
	}
}
