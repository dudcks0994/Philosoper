#include "philo.h"

long long	ft_atoi(const char *s)
{
	int			sum;
	long long	sign;

	sum = 0;
	sign = 1;
	while ((8 < *s && *s < 14) || *s == ' ')
		s++;
	while (47 < *s && *s < 58)
	{
		sum = sum * 10 + (*s - 48);
		if (sum < 0)
			return (-1);
		s++;
	}
	return (sign * sum);
}

int	free_data(t_shared **shared_data)
{
	if (*shared_data == 0)
		return (0);
	if ((*shared_data)->fork != 0)
	{
		free((*shared_data)->fork);
		(*shared_data)->fork = 0;
	}
	if ((*shared_data)->philo != 0)
	{
		free((*shared_data)->philo);
		(*shared_data)->philo = 0;
	}
	if ((*shared_data)->fork_status != 0)
	{
		free((*shared_data)->fork_status);
		(*shared_data)->fork_status = 0;
	}
	free(*shared_data);
	*shared_data = 0;
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

int	check_valid(int argc, char **argv, t_shared *shared_data)
{
	int	i;
	int	j;

	i = 1;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j] != 0)
		{
			if (argv[i][j] == ' ' || (8 < argv[i][j] && argv[i][j] < 14))
				j++;
			else if (47 < argv[i][j] && argv[i][j] < 58)
				j++;
			else
				return (0);
		}
		i++;
	}
	shared_data->philo_num = ft_atoi(argv[1]);
	shared_data->time[DIE] = ft_atoi(argv[2]);
	shared_data->time[EAT] = ft_atoi(argv[3]);
	shared_data->time[SLEEP] = ft_atoi(argv[4]);
	if (shared_data->philo_num < 0 || shared_data->time[DIE] < 0 || \
	shared_data->time[EAT] < 0 || shared_data->time[SLEEP] < 0)
		return (0);
	if (argc == 6)
	{
		shared_data->request_eat = ft_atoi(argv[5]);
		if (shared_data->request_eat < 0)
			return (0);
	}
	else
		shared_data->request_eat = -1;
	return (1);
}

long long	ms(struct timeval a, struct timeval b)
{
	long long	sec;
	long long	usec;

	sec = a.tv_sec - b.tv_sec;
	usec = a.tv_usec - b.tv_usec;
	return (sec * 1000 + usec / 1000);
}
