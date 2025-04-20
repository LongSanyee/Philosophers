/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rammisse <rammisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 14:33:22 by rammisse          #+#    #+#             */
/*   Updated: 2025/04/20 11:26:40 by rammisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->eatmute);
	philo->lastmeal = getcurrenttime();
	philo->eatcount++;
	pthread_mutex_unlock(&philo->data->eatmute);
	printstatus(*philo, "is eating");
	ft_usleep(philo->data->timetoeat);
}

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

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (philo->eatcount == philo->data->musteat)
			return (NULL);
		if (checkdeath(philo->data))
			return (NULL);
		if (philo->id % 2 == 0)
		{
			pick_up(philo->right_fork, philo);
			pick_up(philo->left_fork, philo);
		}
		else
		{
			pick_up(philo->left_fork, philo);
			pick_up(philo->right_fork, philo);
		}
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		ft_eat(philo);
		ft_sleep(*philo);
		ft_think(*philo);
	}
}
