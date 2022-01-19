/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kennyduong <kennyduong@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 17:29:18 by chduong           #+#    #+#             */
/*   Updated: 2022/01/17 23:14:15 by kennyduong       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	print_status(t_philo *philo, int status)
{
	long int	time;
	bool		dead;

	dead = check_dead(philo->data);
	time = get_time(philo->data);
	pthread_mutex_lock(&philo->data->lock_print);
	if (status == DEAD)
		printf("%ld ms\t | %d died\t\t💀\n", time, philo->id);
	else if (status == FORK && !dead)
		printf("%ld ms\t | %d has taken a fork\t🍴\n", time, philo->id);
	else if (status == EAT && !dead)
		printf("%ld ms\t | %d is eating\t\t🍝\n", time, philo->id);
	else if (status == SLEEP && !dead)
		printf("%ld ms\t | %d is sleeping\t💤\n", time, philo->id);
	else if (status == THINK && !dead)
		printf("%ld ms\t | %d is thinking\t💭\n", time, philo->id);
	pthread_mutex_unlock(&philo->data->lock_print);
}

void	ft_usleep(int duration, t_data *data)
{
	long	start;
	long	current;

	start = get_time(data);
	current = start;
	while (duration > current - start)
	{
		if (check_dead(data) || check_allfinish(data))
			return ;
		usleep(100);
		current = get_time(data);
	}
}

bool	check_dead(t_data *data)
{
	bool	ret;

	pthread_mutex_lock(&data->lock_dead);
	ret = data->dead;
	pthread_mutex_unlock(&data->lock_dead);
	return (ret);
}

bool	check_allfinish(t_data *data)
{
	bool	ret;

	pthread_mutex_lock(&data->lock_finish);
	ret = data->all_finish;
	pthread_mutex_unlock(&data->lock_finish);
	return (ret);
}

void	free_all(t_data *data)
{
	if (data->fork)
		free(data->fork);
	data->fork = NULL;
	if (data->philo)
		free(data->philo);
	data->philo = NULL;
}
