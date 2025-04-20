/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norm.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rammisse <rammisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 11:34:59 by rammisse          #+#    #+#             */
/*   Updated: 2025/04/20 11:42:06 by rammisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	setisdie(t_data *data)
{
	pthread_mutex_lock(&data->death);
	data->isdead = 1;
	pthread_mutex_unlock(&data->death);
}
