/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rammisse <rammisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 14:33:22 by rammisse          #+#    #+#             */
/*   Updated: 2025/04/21 14:44:06 by rammisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_eat(t_philo *philo)
{
	if (philo->id % 2 == 0)
		pick_up(philo);
	else
		pickup2(philo);
	printstatus(*philo, "is eating");
	pthread_mutex_lock(&philo->data->eatmute);
	philo->lastmeal = getcurrenttime();
	philo->eatcount++;
	pthread_mutex_unlock(&philo->data->eatmute);
	ft_usleep(philo->data->timetoeat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	printstatus(*philo, "is sleeping");
	ft_usleep(philo->data->timetosleep);
	printstatus(*philo, "is thinking");
}

int	checkallate(t_data *data)
{
	int	i;
	int	res;

	res = 0;
	i = 0;
	while (i < data->numofphilo)
	{
		pthread_mutex_lock(&data->stop);
		if (data->philos[i].allate == 0)
			res++;
		pthread_mutex_unlock(&data->stop);
		i++;
	}
	if (res == data->numofphilo)
		return (1);
	return (0);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->data->numofphilo == 1)
	{
		pthread_mutex_lock(philo->right_fork);
		printstatus(*philo, "has taken a fork");
		ft_usleep(philo->data->timetodie);
		return (pthread_mutex_unlock(philo->right_fork), NULL);
	}
	while (!checkdeath(philo->data))
	{
		ft_eat(philo);
		if (philo->eatcount == philo->data->musteat || checkdeath(philo->data))
		{
			if (philo->eatcount == philo->data->musteat)
			{
				pthread_mutex_lock(&philo->data->stop);
				philo->allate = 0;
				pthread_mutex_unlock(&philo->data->stop);
			}
			return (NULL);
		}
	}
	return (NULL);
}
