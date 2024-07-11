/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lglauch <lglauch@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 14:57:52 by lglauch           #+#    #+#             */
/*   Updated: 2024/04/25 14:03:04 by lglauch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <stdbool.h>
# include <sys/time.h>

# define MAX_INTER 2147483647
# define MIN_INTER -2147483648

typedef struct s_data
{
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_eat;
	long			start;
	int				run;
	pthread_mutex_t	eat_count;
	pthread_mutex_t	last_meal;
	pthread_mutex_t	checker_mutex;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
	pthread_mutex_t	run_mutex;
	pthread_t		monitoring;	
}					t_data;

typedef struct s_philo
{
	bool			alive;
	int				eat;
	int				sleep;
	int				think;
	int				id;
	long			time_last_meal;
	bool			started_eating;
	t_data			*data;
	pthread_t		thread;
}					t_philo;

int		ft_atoi(const char *str);
long	get_time(void);
void	print_action(t_philo *philo, char *action);
int		is_int(const char *str);
int		create_threads(t_data *data, t_philo *philo);
void	*routine(void *arg);
void	*check_status(void *arg);
int		precise_sleep(int milliseconds);
int		finished_eating(t_philo *philo);
void	take_left_fork(t_philo *philo);
void	take_right_fork(t_philo *philo);
void	is_eating(t_philo *philo);
void	pick_up_forks(t_philo *philo);
void	clear_data(t_philo *philo);
int		kill_philo(t_philo *philo);
void	print_action_kill(t_philo *philo, char *action);
void	ft_free_all(t_philo *philo, t_data *data);
int		malloc_all(t_philo **philo, t_data **data, char **argv);
int		check_run(t_philo *philo);
void	run_false(t_philo *philo);
long	ft_get_converted_time(long start);

#endif