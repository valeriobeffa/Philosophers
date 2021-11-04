#ifndef PHILO_H
# define PHILO_H
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_gruppo
{
	int				n_filo;
	int				t_mangia;
	int				t_dorme;
	int				t_muore;
	int				n_pasti;
	int				stampa_d;
	u_int64_t		tempo;
	pthread_mutex_t	*forketta;
	pthread_mutex_t	m_stomping;
	struct s_filo	*filosofo;
}				t_gruppo;

typedef struct s_filo
{
	pthread_t		th;
	pthread_t		check;
	int				morto;
	int				pasti;
	int				num;
	u_int64_t		last_past;
	struct s_gruppo	*gruppo;
}				t_filo;

uint64_t		ft_get_time(void);
t_gruppo		ft_init_gruppo(char **argv);
int				ft_isnum(int c);
int				ft_error(char *s);
int				ft_atoi(const char *str);
int				ft_eggrave(t_filo *filone);
int				ft_num_pasti(t_filo *filone);
int				ft_crea_th_d(t_gruppo *gruppo);
int				ft_check_arg(char **argv, int argc);
int				ft_crea_th_p(t_gruppo *gruppo, t_filo *filo);
void			ft_usleep(int time);
void			*routine(void *filo);
void			ft_eat(t_filo *filone);
void			*check_death(void *filo);
void			ft_sleep(t_filo *filone);
void			ft_think(t_filo *filone);
void			ft_stampa(t_filo *filone, char c);

#endif