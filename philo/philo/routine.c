/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psoares- <psoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 19:04:27 by psoares-          #+#    #+#             */
/*   Updated: 2023/11/10 18:52:42 by psoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	case_one(t_philos *philo)
{
	pthread_mutex_lock(&philo->can_die);
	philo->last_meal = my_time();
	pthread_mutex_unlock(&philo->can_die);
	pthread_mutex_lock(philo->l_fork);
	printing(philo, 'f');
	pthread_mutex_unlock(philo->l_fork);
}

void	eat(t_philos *philo)
{
	pthread_mutex_unlock(&philo->vars->printing);
	if (philo->id % 2 != 0)
	{
		pthread_mutex_lock(philo->l_fork);
		pthread_mutex_lock(philo->r_fork);
	}
	else
	{
		pthread_mutex_lock(philo->r_fork);
		pthread_mutex_lock(philo->l_fork);
	}
	pthread_mutex_lock(&philo->can_die);
	printing(philo, 'f');
	printing(philo, 'f');
	printing(philo, 'e');
	philo->last_meal = my_time();
	pthread_mutex_unlock(&philo->can_die);
	ft_usleep(philo->vars->tte);
	pthread_mutex_lock(&philo->vars->printing);
	philo->n_meals += 1;
	pthread_mutex_unlock(&philo->vars->printing);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

void	*routine(void *philo_void)
{
	t_philos	*philo;

	philo = (t_philos *)philo_void;
	if (philo->vars->n_philos == 1)
	{
		case_one(philo);
		return (NULL);
	}
	pthread_mutex_lock(&philo->vars->printing);
	while (!philo->vars->someone_died
		&& philo->vars->full_philos < philo->vars->n_philos)
	{
		eat(philo);
		printing(philo, 's');
		ft_usleep(philo->vars->tts);
		printing(philo, 't');
		pthread_mutex_lock(&philo->vars->printing);
		usleep(100);
	}
	pthread_mutex_unlock(&philo->vars->printing);
	return (NULL);
}

void	routine_creator(t_philos *philos, t_vars vars)
{
	int	i;

	i = -1;
	while (++i < vars.n_philos)
	{
		philos[i].start_time = my_time();
		if (pthread_create(&philos[i].thread, NULL, &routine,
				(void *)&philos[i]) != 0)
			return ;
		usleep(500);
	}
	monitor_creator(philos);
	i = -1;
	while (++i < vars.n_philos)
		if (pthread_join(philos[i].thread, NULL))
			return ;
}
