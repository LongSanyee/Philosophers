/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rammisse <rammisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 14:33:22 by rammisse          #+#    #+#             */
/*   Updated: 2025/06/03 16:06:08 by rammisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_eathelp(t_philo *philo)
{
	pthread_mutex_unlock(&philo->data->eatmute);
	ft_usleep(philo->data->timetoeat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	if (checkdeath(philo->data))
		return (1);
	return (0);
}

void	ft_eat(t_philo *philo)
{
	if (philo->id % 2 == 0)
		pick_up(philo);
	else
		pickup2(philo);
	if (checkdeath(philo->data))
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return ;
	}
	printstatus(*philo, "is eating");
	pthread_mutex_lock(&philo->data->eatmute);
	philo->lastmeal = getcurrenttime();
	if (philo->data->ac == 6)
		philo->eatcount++;
	if (ft_eathelp(philo) == 1)
		return ;
	printstatus(*philo, "is sleeping");
	ft_usleep(philo->data->timetosleep);
	printstatus(*philo, "is thinking");
	if (checkdeath(philo->data))
		return ;
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->data->numofphilo == 1)
	{
		pthread_mutex_lock(philo->right_fork);
		printstatus(*philo, "has taken a fork");
		printstatus(*philo, "died");
		ft_usleep(philo->data->timetosleep);
		return (pthread_mutex_unlock(philo->right_fork), NULL);
	}
	while (!checkdeath(philo->data))
	{
		ft_eat(philo);
		if (philo->eatcount == philo->data->musteat)
		{
			pthread_mutex_lock(&philo->data->stop);
			philo->data->mustfinish = 1;
			pthread_mutex_unlock(&philo->data->stop);
			return (NULL);
		}
	}
	return (NULL);
}
