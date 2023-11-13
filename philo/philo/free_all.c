/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psoares- <psoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 19:04:21 by psoares-          #+#    #+#             */
/*   Updated: 2023/11/07 19:04:22 by psoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	free_all(pthread_mutex_t *forks, t_philos *philos)
{
	if (forks)
		free(forks);
	if (philos)
		free(philos);
}

void	mutex_destroy(t_vars *vars, t_philos *philos, pthread_mutex_t *forks)
{
	int	i;

	pthread_mutex_destroy(&vars->printing);
	i = -1;
	while (++i < vars->full_philos)
	{
		pthread_mutex_destroy(&philos[i].can_die);
		pthread_mutex_destroy(&forks[i]);
	}
}
