/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 13:33:07 by leo               #+#    #+#             */
/*   Updated: 2024/04/29 10:20:27 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	take_left_fork(t_philo *philo)
{
	pthread_mutex_lock
		(&philo->data->forks[(philo->id % philo->data->nb_philo)]);
	print_action(philo, "has taken a fork");
}

void	take_right_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->forks[(philo->id - 1)]);
	print_action(philo, "has taken a fork");
}

void	is_eating(t_philo *philo)
{
	print_action(philo, "is eating");
	precise_sleep(philo->data->time_to_eat);
	pthread_mutex_lock(&philo->data->eat_count);
	philo->time_last_meal = get_time();
	philo->started_eating = true;
	philo->eat++;
	pthread_mutex_unlock(&philo->data->eat_count);
	pthread_mutex_unlock
		(&philo->data->forks[(philo->id) % philo->data->nb_philo]);
	pthread_mutex_unlock(&philo->data->forks[philo->id - 1]);
}

void	pick_up_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		take_left_fork(philo);
		take_right_fork(philo);
	}
	else
	{
		take_right_fork(philo);
		take_left_fork(philo);
	}
}

void	print_action_kill(t_philo *philo, char *action)
{
	if (philo->data == NULL || action == NULL)
	{
		printf("Error: Invalid argument\n");
		return ;
	}
	if (philo->data->nb_philo <= 0)
	{
		printf("Error: Invalid philosopher number\n");
		return ;
	}
	pthread_mutex_lock(&philo->data->print);
	printf("%ld %d %s\n", ft_get_converted_time(philo->data->start)
		, philo->id, action);
	pthread_mutex_unlock(&philo->data->print);
}
