/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norm.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rammisse <rammisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 11:34:59 by rammisse          #+#    #+#             */
/*   Updated: 2025/04/20 20:14:48 by rammisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	setisdie(t_data *data)
{
	pthread_mutex_lock(&data->death);
	data->isdead = 1;
	pthread_mutex_unlock(&data->death);
}

int	checkallate(t_data *data)
{
	int	i;
	int	all_ate;

	if (data->musteat > 0)
	{
		all_ate = 1;
		i = 0;
		while (i < data->numofphilo)
		{
			pthread_mutex_lock(&data->eatmute);
			if (data->philos[i++].eatcount < data->musteat)
				all_ate = 0;
			pthread_mutex_unlock(&data->eatmute);
		}
		if (all_ate)
			return (0);
	}
	return (1);
}
