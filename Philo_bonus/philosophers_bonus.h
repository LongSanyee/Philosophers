#ifndef PHILOSOPHERS_BONUS_H
# define PHILOSOPHERS_BONUS_H

# include <semaphore.h>
# include <pthread.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <signal.h>
# include <stdio.h>
# include <sys/time.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_philos	t_philos;

typedef struct s_data
{
	size_t			timetodie;
	size_t			starttime;
	int				numofphilo;
	int				timetosleep;
	int				timetoeat;
	int				musteat;
	int				mustfinish;
	int				ac;
	t_philos		*philos;
	sem_t			*forks;
	sem_t			*dead;
	sem_t			*print;
	sem_t			*eat;
}	t_data;

typedef struct s_philos
{
	pthread_t 		monitor;
	pid_t	pid;
	int				id;
	size_t			lastmeal;
	int				eatcount;
	t_data			*data;

}	t_philos;

int		ispositive_bonus(t_data data, int ac);
void seminit(t_data *data);
int		parse_bonus(char **av);
void	init_bonus(t_data *data, char **av, int ac);
void	initdata_bonus(t_data *data);
void *monitor(void *arg);
size_t	getcurrenttime(void);
int		ft_atoi(char *str);
void	ft_usleep_bonus(size_t num);
int		isnum(char *str);
void routine_bonus(t_philos *philo);

#endif