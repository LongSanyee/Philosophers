/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rammisse <rammisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 10:45:44 by rammisse          #+#    #+#             */
/*   Updated: 2025/06/03 12:26:01 by rammisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_usleep(size_t num)
{
	size_t	start;

	start = getcurrenttime();
	while (getcurrenttime() - start < num)
		usleep(333);
}

void	inithelp(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->numofphilo)
	{
		if (pthread_create(&data->philos[i].threads, NULL,
				routine, (void *)&data->philos[i]) != 0)
			return ;
		i++;
	}
}

void	initmutex(t_data *data)
{
	pthread_mutex_init(&data->eatmute, NULL);
	pthread_mutex_init(&data->printlock, NULL);
	pthread_mutex_init(&data->death, NULL);
	pthread_mutex_init(&data->stop, NULL);
	data->starttime = getcurrenttime();
}

void	initphilos(t_data *data)
{
	int	i;

	i = 0;
	data->forks = malloc(data->numofphilo * sizeof(pthread_mutex_t));
	if (!data->forks)
		return ;
	while (i < data->numofphilo)
		pthread_mutex_init(&data->forks[i++], NULL);
	initmutex(data);
	data->philos = malloc(data->numofphilo * sizeof(t_philo));
	if (!data->philos)
		return ;
	i = -1;
	while (++i < data->numofphilo)
	{
		data->philos[i].data = data;
		data->philos[i].id = i + 1;
		data->philos[i].right_fork = &data->forks[i];
		data->philos[i].left_fork = &data->forks[(i + 1) % data->numofphilo];
		data->philos[i].lastmeal = data->starttime;
		data->philos[i].eatcount = 0;
		data->philos[i].allate = 0;
	}
	inithelp(data);
	pthread_create(&data->monitor, NULL, monitor, data);
}

void	*monitor(void *arg)
{
	int		i;
	t_data	*data;

	data = (t_data *)arg;
	while (1)
	{
		i = -1;
		while (++i < data->numofphilo)
		{
			pthread_mutex_lock(&data->eatmute);
			pthread_mutex_lock(&data->stop);
			if (getcurrenttime() - data->philos[i].lastmeal > data->timetodie)
			{
				setisdie(data);
				printf("%ld %d died\n", getcurrenttime()
					- data->starttime, data->philos[i].id);
				return (pthread_mutex_unlock(&data->stop),
					pthread_mutex_unlock(&data->eatmute), NULL);
			}
			unlockmutex(data);
		}
		if (checkallate(data) || checkdeath(data))
			return (NULL);
		usleep(1000);
	}
}
