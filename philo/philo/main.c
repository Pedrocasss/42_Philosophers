/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psoares- <psoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 19:04:16 by psoares-          #+#    #+#             */
/*   Updated: 2023/11/07 19:04:17 by psoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_philos			*philos;
	t_vars				vars;
	pthread_mutex_t		*forks;

	if (argc < 5 || argc > 6)
	{
		printf("Invalid number of arguments\n");
		printf("Usage: <num_philos> <time to die>");
		printf(" <time to eat> <time to sleep> [num of meals]\n");
		return (1);
	}
	if (!valid_args(argv))
	{
		printf("Some invalid argument\n");
		return (1);
	}
	vars = init_args(argc, argv);
	forks = forks_init(vars);
	philos = philos_init(&vars, forks);
	routine_creator(philos, vars);
	mutex_destroy(&vars, philos, forks);
	free_all(forks, philos);
}
