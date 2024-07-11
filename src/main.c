/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lglauch <lglauch@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 15:06:26 by lglauch           #+#    #+#             */
/*   Updated: 2024/04/25 14:01:39 by lglauch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"
#include <stdlib.h>

void	init_data(t_data *data, char **argv, t_philo *philo)
{
	int	fork_number;

	data->nb_philo = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		data->nb_eat = ft_atoi(argv[5]);
	else
		data->nb_eat = -1;
	fork_number = ft_atoi(argv[1]);
	while (--fork_number >= 0)
		pthread_mutex_init(&data->forks[fork_number], NULL);
	pthread_mutex_init(&data->print, NULL);
	pthread_mutex_init(&data->last_meal, NULL);
	pthread_mutex_init(&data->eat_count, NULL);
	pthread_mutex_init(&data->checker_mutex, NULL);
	pthread_mutex_init(&data->run_mutex, NULL);
	data->start = get_time();
	data->run = true;
	philo->data = data;
}

int	input_check(int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (i < argc)
	{
		j = 0;
		if (!is_int(argv[i]) || argv[i][0] <= '0')
			return (0);
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	malloc_all(t_philo **philo, t_data **data, char **argv)
{
	*philo = malloc(sizeof(t_philo) * ft_atoi(argv[1]));
	if (!*philo)
		return (1);
	*data = malloc(sizeof(t_data));
	if (!*data)
	{
		free(*philo);
		return (1);
	}
	(*data)->forks = malloc(sizeof(pthread_mutex_t) * ft_atoi(argv[1]));
	if (!(*data)->forks)
	{
		free(*data);
		free(*philo);
		return (1);
	}
	return (0);
}

int	case_one(t_philo *philo)
{
	if (philo->data->nb_philo == 1)
	{
		printf("%d %d %s\n", philo->data->time_to_die,
			1, "died");
		precise_sleep(4);
		ft_free_all(philo, philo->data);
		return (1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	*data;
	t_philo	*philo;

	if ((argc == 6 || argc == 5) && input_check(argc, argv))
	{
		if (malloc_all(&philo, &data, argv))
			return (1);
		init_data(data, argv, philo);
		if (case_one(philo))
			return (0);
		create_threads(data, philo);
		clear_data(philo);
		ft_free_all(philo, data);
		return (0);
	}
	else
		printf("Error: Wrong number of arguments\n");
	return (0);
}
