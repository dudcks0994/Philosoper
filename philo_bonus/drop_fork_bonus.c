/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drop_fork_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngcki <youngcki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 17:19:36 by youngcki          #+#    #+#             */
/*   Updated: 2023/08/29 17:19:47 by youngcki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	drop_one_fork_with_box_fail(t_philo *philo)
{
	sem_post(philo->data->fork);
	sem_post(philo->data->fork_box);
	return (-1);
}

int	drop_two_fork_with_box_fail(t_philo *philo)
{
	sem_post(philo->data->fork);
	sem_post(philo->data->fork);
	sem_post(philo->data->fork_box);
	return (-1);
}

int	drop_two_fork_without_box_fail(t_philo *philo)
{
	sem_post(philo->data->fork);
	sem_post(philo->data->fork);
	return (-1);
}
