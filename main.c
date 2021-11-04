#include "philo.h"

void	ft_stampa(t_filo *filone, char c)
{
	pthread_mutex_lock(&filone->gruppo->m_stomping);
	if (c == 'e' && !ft_eggrave(filone) && !ft_num_pasti(filone))
	{
		printf("%llu %d \e[0;33mis eating\e[0m\n", (ft_get_time() - \
		filone->gruppo->tempo), filone->num);
		filone->pasti++;
	}
	else if (c == 't' && !ft_eggrave(filone) && !ft_num_pasti(filone))
		printf("%llu %d \e[0;36mis thinking\e[0m\n", (ft_get_time() - \
		filone->gruppo->tempo), filone->num);
	else if (c == 's' && !ft_eggrave(filone) && !ft_num_pasti(filone))
		printf("%llu %d \e[0;35mis sleeping\e[0m\n", (ft_get_time() - \
		filone->gruppo->tempo), filone->num);
	else if ((c == 'r' || c == 'l') && !ft_eggrave(filone) && \
	!ft_num_pasti(filone))
		printf("%llu %d \e[0;31mhas taken a fork\e[0m\n", (ft_get_time() - \
		filone->gruppo->tempo), filone->num);
	else if (c == 'd')
		printf("%llu %d \e[0;32mdied\e[0m\n", (ft_get_time() - \
		filone->gruppo->tempo), filone->num);
	pthread_mutex_unlock(&filone->gruppo->m_stomping);
}

t_gruppo	ft_init_gruppo(char **argv)
{
	t_gruppo	gruppo;
	int			i;

	i = 0;
	gruppo.n_filo = ft_atoi(argv[1]);
	if (gruppo.n_filo < 1)
		return (gruppo);
	gruppo.t_muore = ft_atoi(argv[2]);
	gruppo.t_mangia = ft_atoi(argv[3]);
	gruppo.t_dorme = ft_atoi(argv[4]);
	gruppo.stampa_d = 0;
	if (argv[5])
		gruppo.n_pasti = ft_atoi(argv[5]);
	else
		gruppo.n_pasti = -1;
	gruppo.forketta = malloc(sizeof(pthread_mutex_t) * gruppo.n_filo);
	if (!gruppo.forketta)
		return (gruppo);
	while (i < gruppo.n_filo)
		pthread_mutex_init(&gruppo.forketta[i++], NULL);
	pthread_mutex_init(&gruppo.m_stomping, NULL);
	gruppo.tempo = ft_get_time();
	return (gruppo);
}

int	ft_check_arg(char **argv, int argc)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	if (argc == 5 || argc == 6)
	{
		while (argv[i])
		{
			while (argv[i][j])
			{
				if (!ft_isnum(argv[i][j]))
					return (ft_error("Error: invalid arguments"));
				j++;
			}
			i++;
			j = 0;
		}
	}
	else
		return (ft_error("Error: invalid arguments"));
	return (1);
}

int	main(int argc, char **argv)
{
	t_gruppo	gruppo;
	t_filo		*filo;
	int			i;

	i = 0;
	filo = NULL;
	if (ft_check_arg(argv, argc))
	{
		gruppo = ft_init_gruppo(argv);
		ft_crea_th_d(&gruppo);
		while (i < gruppo.n_filo)
			pthread_mutex_destroy(&gruppo.forketta[i++]);
		pthread_mutex_destroy(&gruppo.m_stomping);
		free(gruppo.forketta);
		free(filo);
	}
	return (0);
}
