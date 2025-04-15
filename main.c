/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rammisse <rammisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 10:35:06 by rammisse          #+#    #+#             */
/*   Updated: 2025/04/15 14:16:25 by rammisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	init(t_data *data, char **av, int ac)
{
	int	i;

	i = 0;
	data->numofphilo = ft_atoi(av[1]);
	data->timetodie = ft_atoi(av[2]);
	data->timetoeat = ft_atoi(av[3]);
	data->timetosleep = ft_atoi(av[4]);
	if (ac == 6)
		data->musteat = ft_atoi(av[5]);
	data->forks = malloc(data->numofphilo * sizeof(pthread_mutex_t));
	if (!data->forks)
		return ;
	while (i < data->numofphilo)
		pthread_mutex_init(&data->forks[i++], NULL);
	data->philos = malloc(data->numofphilo * sizeof(t_philo));
	if (!data->philos)
		return ;
	i = 0;
	while (i < data->numofphilo)
	{
		data->philos[i].left_fork = &data->forks[i];
		data->philos[i].right_fork = &data->forks[(i + 1) % data->numofphilo];
		i++;
	}
}


int	parse(char **av)
{
	int	i;

	i = 1;
	while (av[i])
	{
		if (!isnum(av[i]))
			return (0);
		i++;
	}
	return (1);
}

int	main(int ac, char **av)
{
	t_data	data;

	if ((ac != 5 && ac != 6) || !parse(av))
		return (printf("Invalid arguments !"), 0);
	init(&data, av, ac);
	if (!ispositive(data, ac))
		return (0);
	return (0);
}
