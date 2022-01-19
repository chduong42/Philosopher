/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chduong <chduong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 17:44:16 by kennyduong        #+#    #+#             */
/*   Updated: 2022/01/18 18:21:35 by chduong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static void	check_finish(t_data *data, t_philo *ph)
{
	int		i;
	int		finished;

	i = 0;
	finished = 0;
	while (data->nb_eat > 0 && i < data->nb_philo)
	{	
		if ((ph + i)->meals >= data->nb_eat)
			++finished;
		if (finished == data->nb_philo)
		{
			pthread_mutex_lock(&data->lock_finish);
			data->all_finish = true;
			pthread_mutex_unlock(&data->lock_finish);
			return ;
		}
		++i;
	}
}

static void	check_death(t_data *data, t_philo *ph)
{
	int	i;
	int	last_time;

	i = 0;
	while (i < data->nb_philo)
	{	
		pthread_mutex_lock(&data->lock_finish);
		last_time = (ph + i)->time_last_meal;
		pthread_mutex_unlock(&data->lock_finish);
		if (last_time + data->time_death <= get_time(data))
		{
			pthread_mutex_lock(&data->lock_dead);
			data->dead = true;
			pthread_mutex_unlock(&data->lock_dead);
			print_status(ph + i, DEAD);
			return ;
		}
		++i;
	}
}

static void	run_simulation(t_data *data)
{
	if (create_mutex(data))
	{
		free_all(data);
		return ;
	}
	data->time_start = get_init_time();
	if (create_threads(data))
	{
		free_all(data);
		return ;
	}
	while (!check_dead(data))
	{
		check_finish(data, data->philo);
		if (check_allfinish(data))
			break ;
		check_death(data, data->philo);
	}
	join_threads(data);
	destroy_threads(data);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (check_arg(ac, av))
	{
		data = parse_arg(ac, av);
		run_simulation(&data);
	}
	return (0);
}
