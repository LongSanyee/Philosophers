/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rammisse <rammisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 14:11:25 by rammisse          #+#    #+#             */
/*   Updated: 2025/06/03 16:07:24 by rammisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_atoi(char *str)
{
	int	i;
	int	sign;
	int	old_result;
	int	result;

	sign = 1;
	i = 0;
	result = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		old_result = result;
		result = result * 10 + str[i] - '0';
		if (old_result != result / 10)
			return (0);
		i++;
	}
	return (result * sign);
}

int	isnum(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (0);
		i++;
	}
	return (1);
}

int	ispositive(t_data data, int ac)
{
	if (data.numofphilo <= 0 || data.timetodie <= 0 || data.timetoeat <= 0
		|| data.timetosleep <= 0)
		return (printf("Invalid Arguments !\n"), 0);
	if (ac == 6)
	{
		if (data.musteat <= 0)
			return (printf("Invalid Arguments !\n"), 0);
	}
	return (1);
}

int	checkdeath(t_data *info)
{
	pthread_mutex_lock(&info->death);
	if (info->isdead == 1)
		return (pthread_mutex_unlock(&info->death), 1);
	pthread_mutex_unlock(&info->death);
	return (0);
}

void	printstatus(t_philo philo, char *str)
{
	long	time;

	pthread_mutex_lock(&philo.data->printlock);
	time = getcurrenttime() - philo.data->starttime;
	if (checkdeath(philo.data) == 0)
		printf("%ld %d %s\n", time, philo.id, str);
	pthread_mutex_unlock(&philo.data->printlock);
}
