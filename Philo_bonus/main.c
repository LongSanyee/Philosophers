#include "philosophers_bonus.h"

int	main(int ac, char **av)
{
	t_data	data;
	int status;
	int		i;

	i = -1;
	if ((ac != 5 && ac != 6) || !parse_bonus(av))
	{
		write(2, "Invalid arguments !\n", 21);
		return (0);
	}
	init_bonus(&data, av, ac);
	if (!ispositive_bonus(data, ac))
		return (0);
	initdata_bonus(&data);
	while (++i < data.numofphilo)
	{
		data.philos[i].pid = fork();
		if (!data.philos[i].pid)
		{
			routine_bonus(&data.philos[i]);
			exit(1);
		}
	}
	return (0);
}
