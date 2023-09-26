/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psoares- <psoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 15:33:18 by psoares-          #+#    #+#             */
/*   Updated: 2023/09/26 18:33:49 by psoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_table *table(void)
{
    static  t_table t;

    return (&t);
}

int main(int argc, char **argv)
{
    t_table *table;
    int i = 0;
    t_philo philosophers;
    
    while (i < table->total_philo)
    {
        
    }
    
}