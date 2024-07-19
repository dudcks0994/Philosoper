/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngcki <youngcki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 11:58:28 by youngcki          #+#    #+#             */
/*   Updated: 2024/07/04 20:33:52 by youngcki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
# include <stdio.h>

#define LEFT 0
#define RIGHT 1

#define DIE 0
#define EAT 1
#define SLEEP 2
#define THINK 3
#define FORK 4

typedef struct s_shared
{
	pthread_mutex_t		*fork;
	pthread_mutex_t		begin;
	pthread_mutex_t		all_eat_check;
	pthread_mutex_t		print;
	pthread_t			*philo;
	char				anyone_die;
	int					*fork_status;
	int					eat_done;
	int					philo_num;
	int					alone_flag;
	long long			time[3];
	long long			time_die;
	long long			time_eat;
	long long			time_sleep;
	int					request_eat;
	struct timeval		init_t;
}t_shared;

typedef struct s_philo
{
	int					philo_name;
	int					eat_count;
	int					*left_fork;
	pthread_mutex_t		*left_fork_mutex;
	int					*right_fork;
	pthread_mutex_t		*right_fork_mutex;
	struct timeval		last_eat;
	t_shared			*shared_data;
}						t_philo;

void* start_routine(void *tmp);

int 	print_behavior(t_philo *philo, int behavior);
long long	ft_atoi(const char *s);
int	free_data(t_shared **shared_data);
void	all_join(t_shared *data);
int	check_valid(int argc, char **argv, t_shared *shared_data);
long long	ms(struct timeval a, struct timeval b);

#endif
