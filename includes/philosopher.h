/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kennyduong <kennyduong@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 17:18:07 by chduong           #+#    #+#             */
/*   Updated: 2022/01/17 23:34:58 by kennyduong       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <stdbool.h>
# include <pthread.h>
# include <sys/time.h>

// MACRO
# define DEAD	0
# define FORK	1
# define EAT	2
# define SLEEP	3
# define THINK	4

//	TYPEDEF
typedef unsigned int	t_uint;
typedef struct s_philo	t_philo;
typedef struct s_data	t_data;

//	STRUCTURES
struct s_data
{
	bool				dead;
	bool				all_finish;
	int					nb_eat;
	int					nb_philo;
	int					time_death;
	int					time_eat;
	int					time_sleep;
	long int			time_start;
	t_philo				*philo;
	pthread_mutex_t		*fork;
	pthread_mutex_t		lock_dead;
	pthread_mutex_t		lock_finish;
	pthread_mutex_t		lock_print;
};

struct s_philo
{
	int					id;
	int					meals;
	long int			time_last_meal;
	pthread_t			th;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	t_data				*data;
};

//	UTILS
int			ft_isdigit(int c);
bool		check_dead(t_data *t_data);
bool		check_allfinish(t_data *t_data);

void		free_all(t_data *data);
void		ft_usleep(int duration, t_data *data);
void		print_status(t_philo *philo, int status);

long int	ft_atoli(const char *str);
long int	get_init_time(void);
long int	get_time(t_data *data);

//	CHECKING & PARSING ARG
int			check_arg(int ac, char **av);
t_data		parse_arg(int ac, char **av);

//	ROUTINE
void		*routine(void *arg);

//	THREAD FUNCTIONS
int			create_mutex(t_data *data);
int			create_threads(t_data *data);
void		join_threads(t_data *data);
void		destroy_threads(t_data *data);

#endif