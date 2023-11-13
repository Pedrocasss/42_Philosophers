/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psoares- <psoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 19:04:24 by psoares-          #+#    #+#             */
/*   Updated: 2023/11/10 18:47:07 by psoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_dead(t_philos *philo, int i)
{
	char			*dead;
	__uint64_t		time;

	dead = "died\n";
	if (philo->vars->full_philos == philo->vars->n_philos)
		return ;
	pthread_mutex_lock(&philo->vars->printing);
	time = my_time() - philo->start_time;
	printf("%ld %d %s", time, philo[i].id, dead);
	pthread_mutex_unlock(&philo->vars->printing);
}

void	printing(t_philos *philo, char c)
{
	__uint64_t		time;

	pthread_mutex_lock(&philo->vars->printing);
	if (philo->vars->someone_died
		|| philo->vars->full_philos == philo->vars->n_philos)
	{
		pthread_mutex_unlock(&philo->vars->printing);
		return ;
	}
	time = my_time() - philo->start_time;
	if (c == 'f')
		printf("%ld %d %s\n", time, philo->id, FORK);
	else if (c == 'e')
		printf("%ld %d %s\n", time, philo->id, EAT);
	else if (c == 's')
		printf("%ld %d %s\n", time, philo->id, SLEEP);
	else if (c == 't')
		printf("%ld %d %s\n", time, philo->id, THINK);
	pthread_mutex_unlock(&philo->vars->printing);
}
