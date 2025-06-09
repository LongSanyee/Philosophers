#include "philosophers_bonus.h"

int	ft_atoi(char *str)
{
	int	i;
	int	sign;
	int	old_result;
	int	result;

	sign = 1;
	i = 0;
	result = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		old_result = result;
		result = result * 10 + str[i] - '0';
		if (old_result != result / 10)
			return (0);
		i++;
	}
	return (result * sign);
}

int	isnum(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (0);
		i++;
	}
	return (1);
}

size_t	getcurrenttime(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	ft_usleep_bonus(size_t num)
{
	size_t	start;

	start = getcurrenttime();
	while (getcurrenttime() - start < num)
	{
		usleep(333);
	}
}