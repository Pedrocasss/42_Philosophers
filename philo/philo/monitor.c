/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psoares- <psoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 19:04:30 by psoares-          #+#    #+#             */
/*   Updated: 2023/11/09 11:58:45 by psoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*dying_philo(t_philos *philos, int i)
{
	pthread_mutex_lock(&philos->vars->printing);
	philos->vars->someone_died = 1;
	pthread_mutex_unlock(&philos->vars->printing);
	print_dead(philos, i);
	pthread_mutex_unlock(&philos[i].can_die);
	return (NULL);
}

void	more_meals(t_philos *philos, int i)
{
	philos->vars->full_philos += 1;
	philos[i].flag = 1;
}

void	*monitor(void *philos_void)
{
	t_philos	*philos;
	int			i;

	philos = (t_philos *)philos_void;
	while (philos->vars->full_philos < philos->vars->n_philos)
	{
		i = -1;
		while (++i < philos->vars->n_philos)
		{
			pthread_mutex_lock(&philos[i].can_die);
			if (my_time() - philos[i].last_meal >= philos->vars->ttd)
				return (dying_philo(philos, i));
			pthread_mutex_unlock(&philos[i].can_die);
			pthread_mutex_lock(&philos->vars->printing);
			if (philos[i].n_meals == philos->vars->target_meals
				&& !philos[i].flag)
				more_meals(philos, i);
			pthread_mutex_unlock(&philos->vars->printing);
		}
	}
	return (NULL);
}

void	monitor_creator(t_philos *philos)
{
	pthread_t	th_monitor;

	if (pthread_create(&th_monitor, NULL, &monitor, (void *)philos))
		return ;
	if (pthread_join(th_monitor, NULL))
		return ;
}
