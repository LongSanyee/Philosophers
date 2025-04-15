/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rammisse <rammisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 17:28:38 by rammisse          #+#    #+#             */
/*   Updated: 2025/04/15 15:17:31 by rammisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>

typedef struct s_philo
{
	pthread_t		*philo;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	int				id;
	long			lastmeal;

}	t_philo;

typedef struct s_data
{
	t_philo			*philos;
	pthread_mutex_t	*forks;
	int				numofphilo;
	int				timetodie;
	int				timetosleep;
	int				timetoeat;
	int				musteat;

}	t_data;

int	ft_atoi(char *str);
int	isnum(char *str);
int	ispositive(t_data data, int ac);

#endif