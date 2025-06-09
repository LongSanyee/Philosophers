#include "philosophers_bonus.h"

void	printstatus(t_philos philo, char *str)
{
	long	time;

    sem_wait(philo.data->print);
	time = getcurrenttime() - philo.data->starttime;
	printf("%ld %d %s\n", time, philo.id, str);
    sem_post(philo.data->print);
}

void	pick_up(t_philos *philo)
{
	sem_wait(philo->data->forks);
	printstatus(*philo, "has taken a fork");
	sem_wait(philo->data->forks);
	printstatus(*philo, "has taken a fork");
}

void ft_eat(t_philos *philo)
{
    pick_up(philo);
    printstatus(*philo, "is eating");
    sem_wait(philo->data->eat);
    philo->lastmeal = getcurrenttime();
    if (philo->data->ac == 6)
        philo->data->philos->eatcount++;
    sem_post(philo->data->eat);
    ft_usleep_bonus(philo->data->timetoeat);
    sem_post(philo->data->forks);
    sem_post(philo->data->forks);
    printstatus(*philo, "is sleeping");
    ft_usleep_bonus(philo->data->timetosleep);
    printstatus(*philo, "is thinking");
}

void *monitor(void *arg)
{
    t_philos *philo;

    philo = (t_philos *)arg;
    while (1)
    {
        sem_wait(philo->data->dead);
        if (getcurrenttime() - philo->lastmeal > philo->data->timetodie)
        {
            sem_wait(philo->data->print);
            printf("%ld %d died\n", getcurrenttime()
		        - philo->data->starttime, philo->id);
            sem_post(philo->data->print);
            exit(1);
        }
        sem_post(philo->data->dead);
    }
}

void routine_bonus(t_philos *philo)
{
    pthread_create(&philo->monitor, NULL, monitor, philo);
	pthread_detach(philo->monitor);
    if (philo->data->numofphilo == 1)
    {
        sem_wait(philo->data->forks);
        printstatus(*philo, "has taken a fork");
        printstatus(*philo, "died");
        sem_post(philo->data->forks);
        exit(10);
    }
    while (1)
    {
        ft_eat(philo);
        if (philo->data->ac == 6 && philo->eatcount == philo->data->musteat)
            exit(20);
    }
}
