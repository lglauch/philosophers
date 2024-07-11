/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lglauch <lglauch@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 12:30:20 by lglauch           #+#    #+#             */
/*   Updated: 2024/04/25 13:59:12 by lglauch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	clear_data(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->data->nb_philo)
	{
		pthread_mutex_destroy(&philo->data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&philo->data->print);
	pthread_mutex_destroy(&philo->data->last_meal);
	pthread_mutex_destroy(&philo->data->eat_count);
	pthread_mutex_destroy(&philo->data->checker_mutex);
}

int	kill_philo(t_philo *philo)
{
	run_false(philo);
	print_action_kill(philo, "died");
	return (1);
}

void	ft_free_all(t_philo *philo, t_data *data)
{
	if (data->forks)
	{
		free(data->forks);
	}
	if (data)
	{
		free(data);
	}
	if (philo)
	{
		free(philo);
	}
}

void	run_false(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->run_mutex);
	philo->data->run = false;
	pthread_mutex_unlock(&philo->data->run_mutex);
}

int	check_run(t_philo *philo)
{
	int	run;

	pthread_mutex_lock(&philo->data->run_mutex);
	run = philo->data->run;
	pthread_mutex_unlock(&philo->data->run_mutex);
	return (run);
}
