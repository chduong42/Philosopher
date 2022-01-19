/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chduong <chduong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 14:49:28 by chduong           #+#    #+#             */
/*   Updated: 2022/01/18 21:35:10 by chduong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	create_mutex(t_data *data)
{
	int	i;

	i = 0;
	data->fork = malloc(sizeof(pthread_mutex_t) * data->nb_philo);
	if (!data->fork)
		return (printf("Error : Failed to malloc fork tab\n"));
	while (i < data->nb_philo)
	{
		if (pthread_mutex_init(data->fork + i, NULL))
			return (printf("Error : Failed to init fork %d\n", i + 1));
		++i;
	}
	if (pthread_mutex_init(&data->lock_dead, NULL))
		return (printf("Error : Failed to init lock_dead\n"));
	if (pthread_mutex_init(&data->lock_finish, NULL))
		return (printf("Error : Failed to init lock_finish\n"));
	if (pthread_mutex_init(&data->lock_print, NULL))
		return (printf("Error : Failed to init lock_print\n"));
	return (0);
}

int	init_philo(t_data *data, int i)
{
	t_philo	*ph;

	ph = data->philo + i;
	ph->data = data;
	ph->id = i + 1;
	ph->meals = 0;
	ph->time_last_meal = 0;
	ph->left_fork = data->fork + i;
	if (i == data->nb_philo - 1)
		ph->right_fork = data->fork;
	else
		ph->right_fork = data->fork + i + 1;
	if (pthread_create(&ph->th, NULL, &routine, ph))
		return (printf("Error : Failed to create philo %d\n", i + 1));
	return (0);
}

int	create_threads(t_data *data)
{
	int	i;

	data->philo = malloc(sizeof(t_philo) * data->nb_philo);
	if (!data->philo)
		return (printf("Error : Failed to malloc philo tab\n"));
	i = 0;
	while (i < data->nb_philo)
	{
		init_philo(data, i);
		usleep(1000);
		i += 1;
	}
	return (0);
}

void	join_threads(t_data *data)
{
	int		i;
	t_philo	*ph;

	i = 0;
	while (i < data->nb_philo)
	{
		ph = data->philo + i;
		if (pthread_join(ph->th, NULL))
			printf("Error : Failed to join philo %d\n", i + 1);
		++i;
	}
}

void	destroy_threads(t_data *data)
{
	int	i;

	i = 0;
	if (pthread_mutex_destroy(&data->lock_dead))
		printf("Error : Failed to destroy lock_dead\n");
	if (pthread_mutex_destroy(&data->lock_finish))
		printf("Error : Failed to destroy lock_eat\n");
	if (pthread_mutex_destroy(&data->lock_print))
		printf("Error : Failed to destroy lock_print\n");
	while (i < data->nb_philo)
	{
		if (pthread_mutex_destroy(data->fork + i))
			printf("Error : Failed to destroy fork %d\n", i);
		++i;
	}
	free_all(data);
}
