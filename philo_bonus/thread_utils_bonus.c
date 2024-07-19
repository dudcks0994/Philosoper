/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_utils_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngcki <youngcki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 14:35:25 by youngcki          #+#    #+#             */
/*   Updated: 2023/08/31 14:37:12 by youngcki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*time_renew(void *tmp)
{
	t_philo			*philo;

	philo = tmp;
	while (1)
	{
		sem_wait(philo->eat_check);
		sem_wait(philo->data->anyone_die);
		philo->eat_count++;
		if (philo->eat_count == philo->data->request_eat)
			philo->data->eat_done++;
		gettimeofday(&philo->last_eat, 0);
		if (philo->die_flag == 1)
		{
			sem_post(philo->data->anyone_die);
			break ;
		}
		sem_post(philo->data->anyone_die);
	}
	return (0);
}

void	its_time_to_die(t_philo *philo, struct timeval cur)
{
	sem_wait(philo->data->print);
	gettimeofday(&cur, 0);
	if (ms(&cur, &philo->last_eat) > philo->data->time_die)
		printf("%dms %d is dead\n", \
		ms(&cur, &philo->data->init_t), philo->philo_name);
	philo->data->anyone_die_flag = 1;
	philo->die_flag = 1;
}

void	*dead_check(void *tmp)
{
	t_philo			*philo;
	t_shared		*data;
	struct timeval	cur;

	philo = tmp;
	data = philo->data;
	while (1)
	{
		sem_wait(philo->data->anyone_die);
		gettimeofday(&cur, 0);
		if (data->anyone_die_flag == 1 || \
		ms(&cur, &philo->last_eat) > data->time_die || \
		(data->request_eat != -1 && data->eat_done == data->philo_num))
		{
			if (data->anyone_die_flag == 1)
				philo->die_flag = 1;
			else
				its_time_to_die(philo, cur);
			sem_post(philo->eat_check);
			sem_post(philo->data->anyone_die);
			break ;
		}
		sem_post(philo->data->anyone_die);
	}
	return (0);
}

void	start_thread(t_philo *philo)
{
	pthread_create(&philo->check_time, 0, time_renew, (void *)philo);
	pthread_create(&philo->go_to_die, 0, dead_check, (void *)philo);
}
