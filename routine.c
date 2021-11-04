#include "philo.h"

void	ft_eat(t_filo *filone)
{
	pthread_mutex_lock(&filone->gruppo->forketta[filone->num - 1]);
	if (filone->num == filone->gruppo->n_filo)
		pthread_mutex_lock(&filone->gruppo->forketta[0]);
	else
		pthread_mutex_lock(&filone->gruppo->forketta[filone->num]);
	ft_stampa(filone, 'l');
	ft_stampa(filone, 'r');
	filone->last_past = ft_get_time();
	ft_stampa(filone, 'e');
	ft_usleep(filone->gruppo->t_mangia);
}

void	ft_sleep(t_filo *filone)
{
	pthread_mutex_unlock(&filone->gruppo->forketta[filone->num - 1]);
	if (filone->num == filone->gruppo->n_filo)
		pthread_mutex_unlock(&filone->gruppo->forketta[0]);
	else
		pthread_mutex_unlock(&filone->gruppo->forketta[filone->num]);
	ft_stampa(filone, 's');
	ft_usleep(filone->gruppo->t_dorme);
}

void	ft_think(t_filo *filone)
{
	ft_stampa(filone, 't');
}

int	ft_eggrave(t_filo *filo)
{
	int		i;
	t_filo	*filone;

	i = 0;
	filone = filo->gruppo->filosofo;
	while (i < filone->gruppo->n_filo)
	{
		if (filone[i].morto == 1)
			return (1);
		i++;
	}
	return (0);
}
