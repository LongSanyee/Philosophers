/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rammisse <rammisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 14:33:22 by rammisse          #+#    #+#             */
/*   Updated: 2025/04/20 20:18:27 by rammisse         ###   ########.fr       */
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

void	pick_up(pthread_mutex_t *fork, t_philo *philo)
{
	pthread_mutex_lock(fork);
	printstatus(*philo, "has taken a fork");
}

void	ft_eat(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pick_up(philo->left_fork, philo);
		pick_up(philo->right_fork, philo);
	}
	else
	{
		pick_up(philo->right_fork, philo);
		pick_up(philo->left_fork, philo);
	}
	printstatus(*philo, "is eating");
	pthread_mutex_lock(&philo->data->eatmute);
	philo->lastmeal = getcurrenttime();
	pthread_mutex_unlock(&philo->data->eatmute);
	ft_usleep(philo->data->timetoeat);
	pthread_mutex_lock(&philo->data->eatmute);
	philo->eatcount++;
	pthread_mutex_unlock(&philo->data->eatmute);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->data->numofphilo == 1)
	{
		printstatus(*philo, "has taken a fork");
		ft_usleep(philo->data->timetodie);
		return (NULL);
	}
	while (1)
	{
		if (philo->eatcount == philo->data->musteat)
			return (NULL);
		if (checkdeath(philo->data))
			return (NULL);
		ft_eat(philo);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		ft_sleep(*philo);
		ft_think(*philo);
	}
}
