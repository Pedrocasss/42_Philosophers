/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psoares- <psoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 19:04:19 by psoares-          #+#    #+#             */
/*   Updated: 2023/11/07 19:04:20 by psoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	mutex_init(t_vars *vars, t_philos *philos)
{
	int	i;

	if (pthread_mutex_init(&vars->printing, NULL))
		return ;
	i = -1;
	while (++i < vars->n_philos)
		if (pthread_mutex_init(&philos[i].can_die, NULL))
			return ;
}

t_philos	*philos_init(t_vars *vars, pthread_mutex_t *forks)
{
	t_philos			*philos;
	int					i;

	philos = malloc(sizeof(t_philos) * vars->n_philos);
	if (!philos)
		return (NULL);
	mutex_init(vars, philos);
	i = -1;
	while (++i < vars->n_philos)
	{
		philos[i].id = i + 1;
		philos[i].l_fork = &forks[i];
		philos[i].r_fork = &forks[(i + 1) % vars->n_philos];
		philos[i].n_meals = 0;
		philos[i].vars = vars;
		philos[i].last_meal = my_time();
		philos[i].flag = 0;
	}
	return (philos);
}

pthread_mutex_t	*forks_init(t_vars vars)
{
	pthread_mutex_t		*forks;
	int					i;

	forks = malloc(sizeof(pthread_mutex_t) * vars.n_philos);
	if (!forks)
		return (NULL);
	i = -1;
	while (++i < vars.n_philos)
	{
		if (pthread_mutex_init(&forks[i], NULL))
			return (NULL);
	}
	return (forks);
}

t_vars	init_args(int argc, char **argv)
{
	int		i;
	t_vars	vars;

	i = 0;
	vars.n_philos = ft_atoi(argv[++i]);
	vars.ttd = ft_atoi(argv[++i]);
	vars.tte = ft_atoi(argv[++i]);
	vars.tts = ft_atoi(argv[++i]);
	if (argc == 6)
		vars.target_meals = ft_atoi(argv[++i]);
	else
		vars.target_meals = -1;
	vars.full_philos = 0;
	vars.someone_died = 0;
	return (vars);
}

int	valid_args(char **argv)
{
	int	i;

	i = 0;
	while (argv[++i])
	{
		if (!ft_isdigit(argv[i]))
			return (0);
		if (ft_atoi(argv[i]) <= 0)
			return (0);
	}
	return (1);
}
