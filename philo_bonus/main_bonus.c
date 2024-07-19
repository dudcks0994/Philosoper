/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngcki <youngcki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 16:26:11 by youngcki          #+#    #+#             */
/*   Updated: 2023/08/31 14:50:08 by youngcki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	time_elapse(t_philo *philo, int limit)
{
	struct timeval	cur;
	int				max;

	sem_wait(philo->data->print);
	gettimeofday(&cur, 0);
	max = ms(&cur, &philo->data->init_t);
	max += limit;
	sem_post(philo->data->print);
	gettimeofday(&cur, 0);
	while (ms(&cur, &philo->data->init_t) < max)
	{
		usleep(100);
		gettimeofday(&cur, 0);
	}
	return (0);
}

int	fork_and_eating(t_philo *philo)
{
	sem_wait(philo->data->fork_box);
	sem_wait(philo->data->fork);
	print_fork(philo, philo->data->init_t, philo->philo_name);
	sem_wait(philo->data->fork);
	print_fork(philo, philo->data->init_t, philo->philo_name);
	print_eating(philo, philo->data->init_t, philo->philo_name);
	sem_post(philo->data->fork_box);
	sem_post(philo->eat_check);
	time_elapse(philo, philo->data->time_eat);
	drop_two_fork_without_box_fail(philo);
	return (0);
}

void	process_philo(t_philo *philo)
{
	sem_wait(philo->data->begin);
	while (1)
	{
		fork_and_eating(philo);
		sleeping(philo, philo->data->init_t, philo->philo_name);
		print_thinking(philo, philo->data->init_t, philo->philo_name);
	}
	exit(0);
}

void	start_process(t_philo *philo)
{
	int	i;

	sem_wait(philo->data->begin);
	i = 0;
	gettimeofday(&philo->data->init_t, 0);
	while (i < philo->data->philo_num)
	{
		philo[i].last_eat = philo->data->init_t;
		philo[i].pid = fork();
		if (philo[i].pid == 0)
			process_philo(&philo[i]);
		i++;
	}
	usleep(100);
	i = 0;
	while (i < philo->data->philo_num)
	{
		start_thread(&philo[i]);
		sem_post(philo->data->begin);
		i++;
	}
	all_join_thread(philo);
	all_kill_process(philo);
}

int	main(int c, char **v)
{
	t_philo		*philo;
	t_shared	*data;
	int			i;

	i = 0;
	if (c != 5 && c != 6)
		return (1);
	if (check_valid(c, v) != 0)
		return (1);
	data = (t_shared *)malloc(sizeof(t_shared));
	if (data == 0)
		exit(1);
	if (init_info(c, v, data) != 0)
		exit(1);
	philo = (t_philo *)malloc(sizeof(t_philo) * data->philo_num);
	if (philo == 0)
		exit(1);
	set_philo(data, philo);
	unlink_sem(philo);
	init_sem(data);
	start_process(philo);
	return_all_process(philo);
	unlink_sem(philo);
	exit(0);
}
