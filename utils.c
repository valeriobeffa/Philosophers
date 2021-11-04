#include "philo.h"

int	ft_isnum(int c)
{
	int	x;

	x = (unsigned char)c;
	if (c < 0 || c > 255)
		return (0);
	if (x >= '0' && x <= '9')
		return (1);
	else
		return (0);
}

int	ft_error(char *s)
{
	printf("%s\n", s);
	return (0);
}

int	ft_atoi(const char *str)
{
	int	x;
	int	y;
	int	len;

	x = 1;
	y = 0;
	len = 0;
	while (*str == 32 || (*str <= 13 && *str >= 9))
		str++;
	if (*str == 43 || *str == 45)
	{
		if (*str == 45)
			x = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9' && len++ > -1)
	{
		y = y * 10 + (*str - '0');
		str++;
	}
	if (y > -2147483648 && y < 2147483647 && len > 18 && x == 1)
		return (-1);
	if (y > -2147483648 && y < 2147483647 && len > 18 && x == -1)
		return (0);
	return (x * y);
}

uint64_t	ft_get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	ft_usleep(int time)
{
	unsigned long	end;

	end = ft_get_time() + time;
	while (ft_get_time() < end)
		usleep(time);
}
