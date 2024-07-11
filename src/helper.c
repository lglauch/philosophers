/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lglauch <lglauch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 12:16:28 by lglauch           #+#    #+#             */
/*   Updated: 2024/04/29 18:52:47 by lglauch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	ft_atoi(const char *str)
{
	int		j;
	int		sign;
	long	result;

	j = 0;
	sign = 1;
	while (str[j] == '\t' || str[j] == ' ' || str[j] == '\r'
		|| str[j] == '\f' || str[j] == '\n' || str[j] == '\v')
		j++;
	if (str[j] == '+' || str[j] == '-')
	{
		if (str[j] == '-')
			sign = -1;
		j++;
	}
	result = 0;
	while (str[j] != 0 && str[j] >= 48 && str[j] <= 57)
	{
		result = (result * 10) + (str[j] - '0');
		j++;
	}
	return (result * sign);
}

int	is_int(const char *str)
{
	int		j;
	int		sign;
	long	result;

	j = 0;
	sign = 1;
	while (str[j] == '\t' || str[j] == ' ' || str[j] == '\r'
		|| str[j] == '\f' || str[j] == '\n' || str[j] == '\v')
		j++;
	if (str[j] == '+' || str[j] == '-')
	{
		if (str[j] == '-')
			sign = -1;
		j++;
	}
	result = 0;
	while (str[j] != 0 && str[j] >= 48 && str[j] <= 57)
	{
		result = (result * 10) + (str[j] - '0');
		j++;
	}
	if (result * sign > MAX_INTER || result * sign < MIN_INTER)
		return (0);
	return (1);
}

long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

long	ft_get_converted_time(long start)
{
	return (get_time() - start);
}

void	print_action(t_philo *philo, char *action)
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
	if (philo->data->run)
		printf("%ld %d %s\n", ft_get_converted_time(philo->data->start), philo->id, action);
	pthread_mutex_unlock(&philo->data->print);
}
