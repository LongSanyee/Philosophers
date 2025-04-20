/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rammisse <rammisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 17:28:38 by rammisse          #+#    #+#             */
/*   Updated: 2025/04/20 11:37:28 by rammisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>

typedef struct s_data	t_data;

typedef struct s_philo
{
	pthread_t		threads;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	int				id;
	size_t			lastmeal;
	int				eatcount;
	t_data			*data;

}	t_philo;

typedef struct s_data
{
	t_philo			*philos;
	pthread_mutex_t	printlock;
	pthread_mutex_t	eatmute;
	pthread_mutex_t	death;
	pthread_t		monitor;
	pthread_mutex_t	*forks;
	size_t			starttime;
	int				numofphilo;
	int				timetodie;
	int				timetosleep;
	int				timetoeat;
	int				musteat;
	int				isdead;

}	t_data;

int		ft_atoi(char *str);
int		isnum(char *str);
int		ispositive(t_data data, int ac);
size_t	getcurrenttime(void);
void	*routine(void *arg);
void	initphilos(t_data *data);
void	ft_usleep(size_t num);
void	printstatus(t_philo philo, char *str);
void	*monitor(void *arg);
void	ft_clear(t_data *data);
int		checkdeath(t_data *info);
void	setisdie(t_data *data);

#endif