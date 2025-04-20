/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rammisse <rammisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 14:33:22 by rammisse          #+#    #+#             */
/*   Updated: 2025/04/20 21:19:36 by rammisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_sleep(t_philo philo)
{
	printstatus(philo, "is sleeping");
	ft_usleep(philo.data->timetosleep);
}

void	ft_think(t_philo philo)
{
	printstatus(philo, "is thinking");
}

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
	while (1)
	{
		if (!checkallate(philo->data))
			return (NULL);
		if (checkdeath(philo->data))
			return (NULL);
		ft_eat(philo);
		ft_sleep(*philo);
		ft_think(*philo);
	}
}
