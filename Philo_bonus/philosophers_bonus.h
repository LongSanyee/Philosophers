#ifndef PHILOSOPHERS_BONUS_H
# define PHILOSOPHERS_BONUS_H

# include <semaphore.h>
# include <fcntl.h>
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
}	t_data;

typedef struct s_philos
{
	int				id;
	size_t			lastmeal;
	int				eatcount;
	t_data			*data;

}	t_philos;

int		ispositive_bonus(t_data data, int ac);
int		parse_bonus(char **av);
void	init_bonus(t_data *data, char **av, int ac);
void	initdata_bonus(t_data *data);
size_t	getcurrenttime(void);
int		ft_atoi(char *str);
int		isnum(char *str);

#endif