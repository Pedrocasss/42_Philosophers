/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psoares- <psoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 15:02:37 by psoares-          #+#    #+#             */
/*   Updated: 2023/09/26 18:12:59 by psoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

typedef struct s_philo
{
    pthread_t   philo;
    int         i;
    pthread_mutex_t *r_fork;
    pthread_mutex_t *l_fork;
    
}               t_philo;


typedef struct s_table
{
    __uint64_t  time_to_eat;
    __uint64_t  time_to_sleep;
    __uint64_t  time_to_die;
    int         total_philo;
    int         times_to_eat;
    
}               t_table;

//utils
int ft_atoi(char *str);

#endif