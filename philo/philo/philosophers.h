/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psoares- <psoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 19:05:27 by psoares-          #+#    #+#             */
/*   Updated: 2023/11/10 19:45:44 by psoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# define FORK "has taken a fork"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>

typedef struct s_vars
{
	int				n_philos;
	int				ttd;
	int				tte;
	int				tts;
	int				target_meals;
	int				full_philos;
	int				someone_died;
	pthread_mutex_t	printing;
}	t_vars;

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	int				n_meals;
	int				flag;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	can_die;
	int				start_time;
	int				last_meal;
	t_vars			*vars;
}	t_philos;

//parse && init
int				valid_args(char **argv);
t_vars			init_args(int argc, char **argv);
pthread_mutex_t	*forks_init(t_vars vars);
t_philos		*philos_init(t_vars *vars, pthread_mutex_t *forks);
void			mutex_init(t_vars *vars, t_philos *philos);
//utils
int				my_time(void);
int				ft_usleep(size_t milliseconds);
int				ft_isdigit(char *str);
int				ft_atoi(const char *str);
//routine
void			routine_creator(t_philos *philos, t_vars vars);
void			*routine(void *philo_void);
void			eat(t_philos *philo);
void			case_one(t_philos *philo);
void			monitor_creator(t_philos *philos);
void			*monitor(void *philos_void);
void			printing(t_philos *philo, char c);
void			more_meals(t_philos *philos, int i);
void			*dying_philo(t_philos *philos, int i);
void			print_dead(t_philos *philo, int i);
//free stuff
void			mutex_destroy(t_vars *vars, t_philos *philos,
					pthread_mutex_t *forks);
void			free_all(pthread_mutex_t *forks, t_philos *philos);

#endif