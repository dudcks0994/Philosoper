/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   return_utils_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngcki <youngcki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 14:34:24 by youngcki          #+#    #+#             */
/*   Updated: 2023/08/31 14:34:46 by youngcki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	unlink_sem(t_philo *philo)
{
	int	i;

	i = 0;
	sem_unlink("begin");
	sem_unlink("anyone_die");
	sem_unlink("print");
	sem_unlink("fork");
	sem_unlink("box");
	while (i < philo->data->philo_num)
	{
		sem_unlink(philo[i].sema_name);
		i++;
	}
}

void	return_all_process(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->data->philo_num)
	{
		waitpid(philo[i].pid, 0, 0);
		i++;
	}
}

void	all_join_thread(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->data->philo_num)
	{
		pthread_join(philo[i].check_time, 0);
		pthread_join(philo[i].go_to_die, 0);
		i++;
	}
}

void	all_kill_process(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->data->philo_num)
	{
		kill(philo[i].pid, SIGTERM);
		i++;
	}
}
