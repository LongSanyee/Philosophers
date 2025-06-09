#include "philosophers_bonus.h"

int	ispositive_bonus(t_data data, int ac)
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

int	parse_bonus(char **av)
{
	int	i;

	i = 1;
	while (av[i])
	{
		if (!isnum(av[i]))
			return (0);
		i++;
	}
	return (1);
}

void	init_bonus(t_data *data, char **av, int ac)
{
	data->numofphilo = ft_atoi(av[1]);
	data->timetodie = ft_atoi(av[2]);
	data->timetoeat = ft_atoi(av[3]);
	data->timetosleep = ft_atoi(av[4]);
	data->mustfinish = 0;
	data->ac = ac;
	if (ac == 6)
		data->musteat = ft_atoi(av[5]);
}

void seminit(t_data *data)
{
	data->dead = sem_open("/dead", O_CREAT, 0644, 1);
	sem_unlink("/forks");
	data->forks = sem_open("/forks", O_CREAT, 0644, data->numofphilo);
	data->eat = sem_open("/eat", O_CREAT, 0644, 1);
	data->print = sem_open("/print", O_CREAT, 0644, 1);
	data->starttime = getcurrenttime();
}

void	initdata_bonus(t_data *data)
{
	int	i;

	i = -1;
	data->philos = malloc(data->numofphilo * sizeof(t_philos));
	if (!data->philos)
		return ;
	seminit(data);
	while (++i < data->numofphilo)
	{
		data->philos[i].id = i + 1;
		data->philos[i].data = data;
		data->philos[i].lastmeal = data->starttime;
		data->philos[i].eatcount = 0;
	}
}
