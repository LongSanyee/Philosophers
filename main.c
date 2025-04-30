/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rammisse <rammisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 10:35:06 by rammisse          #+#    #+#             */
/*   Updated: 2025/04/24 19:43:12 by rammisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

size_t	getcurrenttime(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	ft_clear(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->numofphilo)
		pthread_mutex_destroy(&data->forks[i++]);
	pthread_mutex_destroy(&data->eatmute);
	pthread_mutex_destroy(&data->printlock);
	pthread_mutex_destroy(&data->death);
	pthread_mutex_destroy(&data->stop);
	free(data->forks);
	free(data->philos);
}

void	init(t_data *data, char **av, int ac)
{
	int	i;

	i = 0;
	data->numofphilo = ft_atoi(av[1]);
	data->timetodie = ft_atoi(av[2]);
	data->timetoeat = ft_atoi(av[3]);
	data->timetosleep = ft_atoi(av[4]);
	data->isdead = 0;
	data->ac = ac;
	if (ac == 6)
		data->musteat = ft_atoi(av[5]);
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
	int		i;

	i = 0;
	if ((ac != 5 && ac != 6) || !parse(av))
		return (printf("Invalid arguments !"), 0);
	init(&data, av, ac);
	if (!ispositive(data, ac))
		return (0);
	initphilos(&data);
	pthread_join(data.monitor, NULL);
	while (i < data.numofphilo)
	{
		pthread_join(data.philos[i].threads, NULL);
		i++;
	}
	ft_clear(&data);
	return (0);
}
