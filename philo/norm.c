/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norm.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rammisse <rammisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 11:34:59 by rammisse          #+#    #+#             */
/*   Updated: 2025/06/04 18:17:56 by rammisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	setisdie(t_data *data)
{
	pthread_mutex_lock(&data->death);
	data->isdead = 1;
	pthread_mutex_unlock(&data->death);
}

void	pick_up(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	printstatus(*philo, "has taken a fork");
	pthread_mutex_lock(philo->left_fork);
	printstatus(*philo, "has taken a fork");
}

void	pickup2(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	printstatus(*philo, "has taken a fork");
	pthread_mutex_lock(philo->right_fork);
	printstatus(*philo, "has taken a fork");
}

void	unlockmutex(t_data *data)
{
	pthread_mutex_unlock(&data->stop);
	pthread_mutex_unlock(&data->eatmute);
}

void	monitorhelp(t_data *data, int i)
{
	setisdie(data);
	pthread_mutex_lock(&data->printlock);
	printf("%ld %d died\n", getcurrenttime()
		- data->starttime, data->philos[i].id);
	pthread_mutex_unlock(&data->printlock);
	pthread_mutex_unlock(&data->stop);
	pthread_mutex_unlock(&data->eatmute);
}
