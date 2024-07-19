/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngcki <youngcki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 16:26:20 by youngcki          #+#    #+#             */
/*   Updated: 2023/08/31 14:48:24 by youngcki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <semaphore.h>
# include <unistd.h>
# include <sys/time.h>
# include <string.h>
# include <signal.h>

typedef struct s_shared
{
	sem_t			*anyone_die;
	sem_t			*fork_box;
	sem_t			*fork;
	sem_t			*print;
	sem_t			*begin;
	int				anyone_die_flag;
	int				philo_num;
	int				request_eat;
	int				eat_done;
	int				time_eat;
	int				time_sleep;
	int				time_die;
	struct timeval	init_t;
}				t_shared;

typedef struct s_philo
{
	pthread_t		check_time;
	pthread_t		go_to_die;
	sem_t			*eat_check;
	struct timeval	last_eat;
	int				pid;
	int				philo_name;
	char			*sema_name;
	int				eat_count;
	int				die_flag;
	t_shared		*data;
	struct s_philo	*philo_addr;
}					t_philo;

// etc_utils_bonus.

int				ft_atoi(const char *s);
int				ms(struct timeval *a, struct timeval *b);
char			*ft_itoa(int n);
int				check_valid(int c, char **v);

// drop_fork_bonus.c

int				drop_two_fork_with_box_fail(t_philo *philo);
int				drop_one_fork_with_box_fail(t_philo *philo);
int				drop_two_fork_without_box_fail(t_philo *philo);

// init_tuils_bonus.c

int				init_info(int c, char **v, t_shared *data);
void			init_sem(t_shared *data);
void			set_philo(t_shared *data, t_philo *philo);

// main_bonus.c

int				time_elapse(t_philo *philo, int limit);
int				fork_and_eating(t_philo *philo);
void			process_philo(t_philo *philo);
void			start_process(t_philo *philo);

// print_utils_bonus.c

int				print_eating(t_philo *philo, struct timeval init_t, int name);
int				print_fork(t_philo *philo, struct timeval init_t, int name);
int				sleeping(t_philo *philo, struct timeval init_t, int name);
int				print_thinking(t_philo *philo, struct timeval init_t, int name);

// return_utils_bonus.c

void			all_kill_process(t_philo *philo);
void			all_join_thread(t_philo *philo);
void			return_all_process(t_philo *philo);
void			unlink_sem(t_philo *philo);

// thread_utils_bonus.c

void			*time_renew(void *tmp);
void			its_time_to_die(t_philo *philo, struct timeval cur);
void			*dead_check(void *tmp);
void			start_thread(t_philo *philo);

#endif
