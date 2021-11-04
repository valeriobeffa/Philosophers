#include "philo.h"

int	ft_num_pasti(t_filo *filo_app)
{
	int		i;
	int		j;
	t_filo	*filone;

	i = 0;
	j = 0;
	filone = filo_app->gruppo->filosofo;
	if (filo_app->gruppo->n_pasti == -1)
		return (0);
	while (i < filone->gruppo->n_filo)
	{
		if (filone[i].pasti < filone->gruppo->n_pasti)
			return (0);
		i++;
	}
	return (1);
}

void	*routine(void *filo)
{
	t_filo	*filone;
	int		i;

	filone = (t_filo *)filo;
	i = 0;
	while (!ft_eggrave(filone) && !ft_num_pasti(filone) && \
	 filone->gruppo->n_filo != 1)
	{
		ft_eat(filone);
		ft_sleep(filone);
		ft_think(filone);
	}
	return (NULL);
}

void	*ft_check_death(void *filo)
{
	t_filo		*filone;
	u_int64_t	this_moment;
	u_int64_t	check_time;

	filone = (t_filo *)filo;
	while (!ft_eggrave(filone) && !ft_num_pasti(filone))
	{
		this_moment = ft_get_time();
		check_time = this_moment - filone->last_past;
		if (check_time > (u_int64_t)filone->gruppo->t_muore && (this_moment - \
		 filone->gruppo->tempo) > (u_int64_t)filone->gruppo->t_muore && \
		 filone->gruppo->stampa_d == 0)
		{
			filone->morto = 1;
			filone->gruppo->stampa_d = 1;
			ft_stampa(filone, 'd');
		}
		usleep(1000);
	}
	return (NULL);
}

int	ft_crea_th_d(t_gruppo *gruppo)
{
	int		i;
	t_filo	*filo;

	i = 0;
	filo = malloc(sizeof(t_filo) * gruppo->n_filo);
	gruppo->filosofo = filo;
	if (!filo)
		return (ft_error("Error: malloc"));
	while (i < gruppo->n_filo)
	{
		filo[i].morto = 0;
		filo[i].gruppo = gruppo;
		filo[i].num = i + 1;
		filo[i].pasti = 0;
		if (pthread_create(&filo[i].th, NULL, &routine, &filo[i]) != 0)
			return (ft_error("Error"));
		if (pthread_create(&filo[i].check, NULL, &ft_check_death, &filo[i]) \
		 != 0)
			return (ft_error("Error"));
		i = i + 2;
	}
	ft_crea_th_p(gruppo, filo);
	return (0);
}

int	ft_crea_th_p(t_gruppo *gruppo, t_filo *filo)
{
	int	i;

	i = 1;
	while (i < gruppo->n_filo)
	{
		filo[i].morto = 0;
		filo[i].gruppo = gruppo;
		filo[i].num = i + 1;
		filo[i].pasti = 0;
		if (pthread_create(&filo[i].th, NULL, &routine, &filo[i]) != 0)
			return (ft_error("Error"));
		if (pthread_create(&filo[i].check, NULL, &ft_check_death, &filo[i]) \
		!= 0)
			return (ft_error("Error"));
		i = i + 2;
	}
	i = 0;
	while (i < gruppo->n_filo)
	{
		pthread_join(&filo->th[i], NULL);
		pthread_join(&filo->check[i], NULL);
		i++;
	}
	return (0);
}
