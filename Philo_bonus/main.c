#include "philosophers_bonus.h"

int	main(int ac, char **av)
{
	t_data	data;

	if ((ac != 5 && ac != 6) || !parse_bonus(av))
	{
		write(2, "Invalid arguments !\n", 21);
		return (0);
	}
	init_bonus(&data, av, ac);
	if (!ispositive_bonus(data, ac))
		return (0);
}
