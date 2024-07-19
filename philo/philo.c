#include "philo.h"

int check_others_dead(t_philo* philo)
{
	pthread_mutex_lock(&philo->shared_data->print);
	if (philo->shared_data->anyone_die == 1)
	{
		pthread_mutex_unlock(&philo->shared_data->print);
		return (1);
	}
	pthread_mutex_unlock(&philo->shared_data->print);
	return (0);
}

int check_self_dead(t_philo* philo)
{
	struct timeval cur;
	gettimeofday(&cur, 0);
	if (ms(cur, philo->last_eat) >= philo->shared_data->time[DIE])
	{
		pthread_mutex_lock(&philo->shared_data->print);
		printf("%lld %d died\n", ms(cur, philo->shared_data->init_t), philo->philo_name + 1);
		philo->shared_data->anyone_die = 1;
		pthread_mutex_unlock(&philo->shared_data->print);
		return (1);
	}
	return (0);
}

int time_elapse(t_philo* philo, int behavior)
{
	struct timeval init;
	struct timeval cur;
	gettimeofday(&cur, 0);
	int time = philo->shared_data->time[behavior];
	if (behavior == SLEEP)
		time += philo->shared_data->time[SLEEP];
	init = philo->last_eat;
	while (ms(cur, init) < time)
	{
		if (check_others_dead(philo) != 0)
			return (1);
		usleep(200);
		gettimeofday(&cur, 0);

	}
	return (0);
}

int print_behavior(t_philo* philo, int behavior)
{
	struct timeval cur;
	pthread_mutex_lock(&philo->shared_data->print);
	if (philo->shared_data->anyone_die == 1)
	{
		pthread_mutex_unlock(&philo->shared_data->print);
		return (1);
	}
	gettimeofday(&cur, 0);
	if (behavior == 1)
	{
		printf("%lld %d is eating\n", ms(cur, philo->shared_data->init_t), philo->philo_name + 1);
		philo->last_eat = cur;
		if (philo->eat_count != -1)
			philo->eat_count++;
		if (philo->eat_count != -1 && philo->shared_data->request_eat != -1 && philo->eat_count == philo->shared_data->request_eat)
		{
			pthread_mutex_lock(&philo->shared_data->all_eat_check);
			philo->shared_data->eat_done++;
			pthread_mutex_unlock(&philo->shared_data->all_eat_check);
			philo->eat_count = -1;
		}
	}
	else if (behavior == 2)
		printf("%lld %d is sleeping\n", ms(cur, philo->shared_data->init_t), philo->philo_name + 1);
	else if (behavior == 3)
		printf("%lld %d is thinking\n", ms(cur, philo->shared_data->init_t), philo->philo_name + 1);
	else if (behavior == 4)
		printf("%lld %d has taken a fork\n", ms(cur, philo->shared_data->init_t), philo->philo_name + 1);
	pthread_mutex_unlock(&philo->shared_data->print);
	return (0);
}

int try_fork(t_philo *philo, int direction)
{
	pthread_mutex_t* fork = direction == LEFT ? philo->left_fork_mutex : philo->right_fork_mutex;
	int* fork_status = direction == LEFT ? philo->left_fork : philo->right_fork;
	if (pthread_mutex_lock(fork) != 0)
		exit(1);
	if (*fork_status == 0)
	{
		*fork_status = 1;
		if (pthread_mutex_unlock(fork) != 0)
			exit(1);
		return (0);
	}
	else
	{
		if (pthread_mutex_unlock(fork) != 0)
			exit(1);
		return (1);
	}
	return (0);
}

int drop_fork(t_philo *philo, int direction)
{
	pthread_mutex_t* fork = direction == LEFT ? philo->left_fork_mutex : philo->right_fork_mutex;
	int* fork_status = direction == LEFT ? philo->left_fork : philo->right_fork;
	if (pthread_mutex_lock(fork) != 0)
		exit(1);
	*fork_status = 0;
	if (pthread_mutex_unlock(fork) != 0)
		exit(1);
	return (0);
}

int fork_and_eat(t_philo *philo)
{
	if (try_fork(philo, LEFT) != 0)
		return (1);
	if (try_fork(philo, RIGHT) != 0)
	{
		drop_fork(philo, LEFT);
		return (1);
	}
	if (print_behavior(philo, FORK) != 0)
		return (2);
	if (print_behavior(philo, FORK) != 0)
		return (2);
	return (0);
}

void	*start_routine(void *tmp)
{
	t_philo	*philo;
	int	flag;

	philo = tmp;
	pthread_mutex_lock(&(philo->shared_data->begin));
	pthread_mutex_unlock(&(philo->shared_data->begin));
	if (philo->philo_name % 2 == 0)
		usleep(philo->shared_data->philo_num * 1000);
	philo->last_eat = philo->shared_data->init_t;
	while (1)
	{
		flag = fork_and_eat(philo);
		if (flag == 1)
		{
			if (check_others_dead(philo) != 0)
				break ;
			if (check_self_dead(philo) != 0)
				break ;
			usleep(1000);
			continue;
		}
		else if (flag == 2)
			return (0);
		if (print_behavior(philo, EAT) != 0)
			break ;
		if (time_elapse(philo, EAT) != 0)
			break ;
		drop_fork(philo, LEFT);
		drop_fork(philo, RIGHT);
		if (print_behavior(philo, SLEEP) != 0)
			break ;
		if (time_elapse(philo, SLEEP) != 0)
			break ;
		if (print_behavior(philo, THINK) != 0)
			break ;
	}
	return (0);
}