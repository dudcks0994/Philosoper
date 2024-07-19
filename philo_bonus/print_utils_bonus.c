/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngcki <youngcki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 14:33:08 by youngcki          #+#    #+#             */
/*   Updated: 2023/08/31 14:33:32 by youngcki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	print_eating(t_philo *philo, struct timeval init_t, int name)
{
	struct timeval	cur;

	sem_wait(philo->data->print);
	gettimeofday(&cur, 0);
	printf("%dms %d is eating\n", ms(&cur, &init_t), name);
	sem_post(philo->data->print);
	return (0);
}

int	print_fork(t_philo *philo, struct timeval init_t, int name)
{
	struct timeval	cur;

	sem_wait(philo->data->print);
	gettimeofday(&cur, 0);
	printf("%dms %d has taken a fork\n", ms(&cur, &init_t), name);
	sem_post(philo->data->print);
	return (0);
}

int	sleeping(t_philo *philo, struct timeval init_t, int name)
{
	struct timeval	cur;

	sem_wait(philo->data->print);
	gettimeofday(&cur, 0);
	printf("%dms %d is sleeping\n", ms(&cur, &init_t), name);
	sem_post(philo->data->print);
	time_elapse(philo, philo->data->time_sleep);
	return (0);
}

int	print_thinking(t_philo *philo, struct timeval init_t, int name)
{
	struct timeval	cur;

	sem_wait(philo->data->print);
	gettimeofday(&cur, 0);
	printf("%dms %d is thinking\n", ms(&cur, &init_t), name);
	sem_post(philo->data->print);
	return (0);
}
