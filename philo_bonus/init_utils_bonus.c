/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngcki <youngcki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 14:32:12 by youngcki          #+#    #+#             */
/*   Updated: 2023/08/31 14:51:53 by youngcki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	init_info(int c, char **v, t_shared *data)
{
	data->philo_num = ft_atoi(v[1]);
	data->time_die = ft_atoi(v[2]);
	data->time_eat = ft_atoi(v[3]);
	data->time_sleep = ft_atoi(v[4]);
	if (data->philo_num < 0 || data->time_die < 0 || \
	data->time_eat < 0 || data->time_sleep < 0)
		return (-1);
	if (c == 5)
		data->request_eat = -1;
	else
	{
		data->request_eat = ft_atoi(v[5]);
		if (data->request_eat <= 0)
			return (-1);
	}
	data->anyone_die_flag = 0;
	data->eat_done = 0;
	return (0);
}

void	init_sem(t_shared *data)
{
	data->begin = sem_open("begin", O_CREAT, 0644, 1);
	data->anyone_die = sem_open("anyone_die", O_CREAT, 0644, 1);
	data->print = sem_open("print", O_CREAT, 0644, 1);
	data->fork = sem_open("fork", O_CREAT, 0644, data->philo_num);
	data->fork_box = sem_open("box", O_CREAT, 0644, 1);
	if (data->begin < 0 || data->anyone_die < 0 || \
	data->print < 0 || data->fork < 0 || data->fork_box < 0)
		exit(1);
}

void	set_philo(t_shared *data, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < data->philo_num)
	{
		philo[i].data = data;
		philo[i].die_flag = 0;
		philo[i].eat_count = 0;
		philo[i].philo_name = i + 1;
		philo[i].sema_name = ft_itoa(i + 1);
		philo[i].eat_check = sem_open(philo[i].sema_name, O_CREAT, 0644, 0);
		if (philo[i].eat_check < 0)
			exit(1);
		philo[i].philo_addr = philo;
		i++;
	}
}
