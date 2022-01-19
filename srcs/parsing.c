/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chduong <chduong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/31 16:56:02 by kennyduong        #+#    #+#             */
/*   Updated: 2022/01/15 13:04:36 by chduong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static void	print_usage(char *name)
{
	printf("Error :\n");
	printf("\e[1;37musage :\e[0m ");
	printf("%s should take the following arguments :\n", name);
	printf("1) the number of philosophers\n");
	printf("2) the time to die in ms\n");
	printf("3) the time to eat in ms\n");
	printf("4) the time to sleep in ms\n");
	printf("5) (optionnal) the number of times each philosopher must eat\n");
}

static int	check_nodigit(char *arg)
{
	if (*arg == '-')
	{
		printf("Error: arguments must be positive\n");
		return (1);
	}
	if (*arg == '+')
		++arg;
	while (*arg)
	{
		if (!ft_isdigit(*arg))
		{
			printf("Error: only digit argument is accepted\n");
			return (1);
		}
		arg++;
	}
	return (0);
}

static int	check_value(int ac, int av)
{
	if (av > INT_MAX)
	{
		printf("Error: arg %d is over INT_MAX\n", ac);
		return (1);
	}
	if (ac == 1 && av < 1)
	{
		printf("Error: No enough philosopher to eat\n");
		return (1);
	}
	if (ac > 1 && ac < 5 && av <= 0)
	{
		printf("Error: time_to_die or time_to_eat or");
		printf("time_to_sleep can't be null or negative\n");
		return (1);
	}
	if (ac == 5 && av < 1)
	{
		printf("Error: Philosophers must eat at least one time");
		return (1);
	}
	return (0);
}

int	check_arg(int ac, char **av)
{
	int	i;

	i = 1;
	if (ac < 5 || ac > 6)
	{
		print_usage(av[0]);
		return (0);
	}
	while (i < ac)
	{
		if (check_nodigit(av[i]))
			return (0);
		if (check_value(i, ft_atoli(av[i])))
			return (0);
		++i;
	}
	return (1);
}

t_data	parse_arg(int ac, char **av)
{
	t_data	arg;

	arg.nb_philo = ft_atoli(av[1]);
	arg.time_death = ft_atoli(av[2]);
	arg.time_eat = ft_atoli(av[3]);
	arg.time_sleep = ft_atoli(av[4]);
	arg.dead = false;
	arg.all_finish = false;
	arg.time_start = 0;
	if (ac == 6)
		arg.nb_eat = ft_atoli(av[5]);
	else
		arg.nb_eat = 0;
	return (arg);
}
