#include "philo.h"

int	init_mutex(t_shared *shared_data)
{
	int	i;

	if (shared_data->fork == 0)
		return (free_data(&shared_data));
	i = 0;
	while (i < shared_data->philo_num)
	{
		if (pthread_mutex_init(&(shared_data->fork[i]), 0) != 0)
			return (free_data(&shared_data));
		i++;
	}
	if (pthread_mutex_init(&(shared_data->begin), 0) != 0)
		return (free_data(&shared_data));
	if (pthread_mutex_init(&(shared_data->print), 0) != 0)
		return (free_data(&shared_data));
	if (pthread_mutex_init(&(shared_data->all_eat_check), 0) != 0)
		return (free_data(&shared_data));
	if (pthread_mutex_init(&(shared_data->begin), 0) != 0)
		return (free_data(&shared_data));
	return (1);
}

t_philo*	create_philo(t_shared* shared_data)
{
	int	i;

	i = 0;
	shared_data->anyone_die = 0;
	shared_data->eat_done = 0;
	shared_data->philo = malloc(sizeof(pthread_t) * shared_data->philo_num);
	shared_data->fork = malloc(sizeof(pthread_mutex_t) * shared_data->philo_num);
	shared_data->fork_status = malloc(sizeof(int) * shared_data->philo_num);
	printf("here\n");
	while (i < shared_data->philo_num)
	{
		shared_data->fork_status[i] = 0;
		i++;
	}
	if (init_mutex(shared_data) == 0)
		return (0);
	if (shared_data->philo == 0 || shared_data->fork == 0)
		return (0);
	return (malloc(sizeof(t_philo) * shared_data->philo_num));
}

void	make_each_philo(t_shared *shared_data, t_philo *philosophers)
{
	int	i;

	i = 0;
	if (shared_data->philo_num != 1)
		shared_data->alone_flag = 0;
	else
		shared_data->alone_flag = 1;
	while (i < shared_data->philo_num)
	{
		philosophers[i].philo_name = i;
		philosophers[i].shared_data = shared_data;
		philosophers[i].eat_count = 0;
		i++;
	}
}

void monitoring_cctv(t_shared* shared_data)
{
	int i;
	while (1)
	{
		i = 0;
		pthread_mutex_lock(&shared_data->all_eat_check);
		if (shared_data->eat_done >= shared_data->philo_num)
		{
			pthread_mutex_unlock(&shared_data->all_eat_check);
			pthread_mutex_lock(&shared_data->print);
			shared_data->anyone_die = 1;
			pthread_mutex_unlock(&shared_data->print);
			break ;
		}
		pthread_mutex_unlock(&shared_data->all_eat_check);
	}

}

int start_thread(t_shared *shared_data, t_philo *philosophers)
{
	int	i;

	i = 0;
	while (i < shared_data->philo_num)
	{
		philosophers[i].left_fork = &shared_data->fork_status[i];
		if (i == shared_data->philo_num - 1)
			philosophers[i].right_fork = &shared_data->fork_status[0];
		else
			philosophers[i].right_fork = &shared_data->fork_status[i + 1];
		philosophers[i].left_fork_mutex = &shared_data->fork[i];
		if (i == shared_data->philo_num - 1)
			philosophers[i].right_fork_mutex = &shared_data->fork[0];
		else
			philosophers[i].right_fork_mutex = &shared_data->fork[i + 1];
		if (pthread_create(&shared_data->philo[i], 0, start_routine, &philosophers[i]) != 0)
			return (1);
		i++;
	}
	gettimeofday(&shared_data->init_t, 0);
	pthread_mutex_unlock(&shared_data->begin);
	return (0);
}

void *ft_calloc(size_t count, size_t size)
{
	void	*ptr;
	size_t	i;

	ptr = malloc(count * size);
	if (ptr == 0)
		return (0);
	i = 0;
	while (i < count * size)
	{
		*((char *)ptr + i) = 0;
		i++;
	}
	return (ptr);
}

void live_alone(t_shared *shared_data)
{
	printf("0ms 1 has taken a fork\n");
	printf("0ms 1 has taken a fork\n");
	printf("0ms 1 is eating\n");
	printf("0ms 1 is sleeping\n");
	printf("0ms 1 is thinking\n");
	usleep(shared_data->time[DIE] * 1000);
	printf("%lldms 1 is dead\n", shared_data->time[DIE]);
	free_data(&shared_data);
}

int	main(int c, char **v)
{
	t_shared	*shared_data;
	t_philo		*philosophers;
	if (c != 5 && c != 6)
		return (1);
	shared_data = ft_calloc(1, sizeof(t_shared));
	printf("original size is %lu\n", sizeof(t_shared));
	printf("size is %lu\n", sizeof(shared_data));
	if (check_valid(c, v, shared_data) == 0)
	{
		free_data(&shared_data);
		return (1);
	}
	philosophers = create_philo(shared_data);
	if (philosophers == 0)
		return (1);
	if (init_mutex(shared_data) == 0)
	{
		free(philosophers);
		return (1);
	}
	make_each_philo(shared_data, philosophers);
	if (shared_data->alone_flag)
	{
		live_alone(shared_data);
		free(philosophers);
		return (0);
	}
	pthread_mutex_lock(&shared_data->begin);
	if (start_thread(shared_data, philosophers) != 0)
	{
		free(philosophers);
		free_data(&shared_data);
		return (1);
	}
	monitoring_cctv(shared_data);
	all_join(shared_data);
	free(philosophers);
	return (0);
}