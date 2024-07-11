/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 13:07:22 by leo               #+#    #+#             */
/*   Updated: 2024/04/29 10:32:15 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*routine(void *arg)
{
	t_philo			*philo;

	philo = (t_philo *)arg;
	arg = NULL;
	while (check_run(philo) == true)
	{
		if (check_run(philo) == false)
			return (NULL);
		pick_up_forks(philo);
		is_eating(philo);
		if (check_run(philo) == false)
			return (NULL);
		print_action(philo, "is sleeping");
		precise_sleep(philo->data->time_to_sleep);
		if (check_run(philo) == false)
			return (NULL);
		print_action(philo, "is thinking");
	}
	return (NULL);
}

int	create_threads(t_data *data, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		philo[i].id = i + 1;
		philo[i].data = data;
		philo[i].alive = true;
		philo[i].eat = 0;
		philo[i].sleep = 0;
		philo[i].think = 0;
		philo[i].started_eating = false;
		pthread_create(&philo[i].thread, NULL, &routine, &philo[i]);
		precise_sleep(1);
		i++;
	}
	i = 0;
	pthread_create(&data->monitoring, NULL, &check_status, philo);
	while (i < data->nb_philo)
		pthread_join(philo[i++].thread, NULL);
	pthread_join(data->monitoring, NULL);
	return (0);
}

void	*check_status(void *arg)
{
	t_philo	*philo;
	int		i;

	philo = (t_philo *)arg;
	while (check_run(philo) == true)
	{
		i = 0;
		finished_eating(philo);
		while (i < philo->data->nb_philo)
		{
			pthread_mutex_lock(&philo->data->eat_count);
			if (philo[i].started_eating && philo[i].data->time_to_die
				< get_time() - philo[i].time_last_meal)
			{
				kill_philo(&philo[i]);
				pthread_mutex_unlock(&philo->data->eat_count);
				return (NULL);
			}
			pthread_mutex_unlock(&philo->data->eat_count);
			i++;
		}
	}
	return (NULL);
}

int	precise_sleep(int milliseconds)
{
	long	start;

	start = get_time();
	while (get_time() - start < milliseconds)
	{
		usleep(250);
	}
	return (1);
}

int	finished_eating(t_philo *philo)
{
	int	i;

	i = 0;
	if (philo->data->nb_eat == -1)
		return (0);
	while (i < philo->data->nb_philo)
	{
		pthread_mutex_lock(&philo->data->eat_count);
		if (philo[i].eat < philo->data->nb_eat)
		{
			pthread_mutex_unlock(&philo->data->eat_count);
			return (0);
		}
		pthread_mutex_unlock(&philo->data->eat_count);
		i++;
	}
	run_false(philo);
	return (1);
}
