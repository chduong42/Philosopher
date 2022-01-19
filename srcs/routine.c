/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chduong <chduong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 16:51:51 by chduong           #+#    #+#             */
/*   Updated: 2022/01/18 22:40:17 by chduong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static int	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->right_fork);
		print_status(philo, FORK);
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, FORK);
		return (2);
	}
	pthread_mutex_lock(philo->left_fork);
	print_status(philo, FORK);
	if (philo->data->nb_philo < 2)
		return (1);
	pthread_mutex_lock(philo->right_fork);
	print_status(philo, FORK);
	return (2);
}

static void	put_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	if (philo->data->nb_philo < 2)
		return ;
	pthread_mutex_unlock(philo->right_fork);
}

static void	eat(t_philo *philo)
{
	if (take_forks(philo) == 2)
	{
		pthread_mutex_lock(&philo->data->lock_finish);
		philo->time_last_meal = get_time(philo->data);
		pthread_mutex_unlock(&philo->data->lock_finish);
		print_status(philo, EAT);
		ft_usleep(philo->data->time_eat, philo->data);
		pthread_mutex_lock(&philo->data->lock_finish);
		++philo->meals;
		pthread_mutex_unlock(&philo->data->lock_finish);
	}
	else
		while (!check_dead(philo->data))
			;
	put_forks(philo);
}

static void	sleep_think(t_philo *philo)
{
	print_status(philo, SLEEP);
	ft_usleep(philo->data->time_sleep, philo->data);
	print_status(philo, THINK);
}

void	*routine(void *philosopher)
{
	t_philo	*ph;

	ph = (t_philo *)philosopher;
	if (ph->id % 2 == 0)
		usleep(5000);
	while (!check_dead(ph->data) && !check_allfinish(ph->data))
	{
		eat(ph);
		if (check_dead(ph->data) || check_allfinish(ph->data))
			break ;
		sleep_think(ph);
	}
	return (NULL);
}
