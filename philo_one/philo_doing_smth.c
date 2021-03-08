/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_doing_smth.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snorthmo <snorthmo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 16:46:56 by snorthmo          #+#    #+#             */
/*   Updated: 2021/03/08 15:23:10 by snorthmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	philo_eating(int i)
{
	pthread_mutex_lock(g_philo[i]->left_fork);
	pthread_mutex_lock(g_philo[i]->right_fork);
	pthread_mutex_lock(&g_philo[i]->eat_mutex);
	pthread_mutex_lock(&g_struct.print_mutex);
	printf("%ld %i has taken a fork\n", subtract_time(g_struct.start_time), \
	i + 1);
	printf("%ld %i has taken a fork\n", subtract_time(g_struct.start_time), \
	i + 1);
	gettimeofday(&g_philo[i]->last_time_eat, NULL);
	pthread_mutex_unlock(&g_struct.print_mutex);
	pthread_mutex_lock(&g_struct.print_mutex);
	printf("%ld %i is eating\n", subtract_time(g_struct.start_time), i + 1);
	pthread_mutex_unlock(&g_struct.print_mutex);
	pthread_mutex_unlock(&g_philo[i]->eat_mutex);
	usleep(g_struct.time_to_eat);
	pthread_mutex_unlock(g_philo[i]->left_fork);
	pthread_mutex_unlock(g_philo[i]->right_fork);
	g_philo[i]->times_eat++;
	if (g_philo[i]->times_eat == g_struct.num_to_eat)
		g_struct.full_philos++;
}
