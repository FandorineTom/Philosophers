/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_doing_smth_three.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snorthmo <snorthmo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 16:46:56 by snorthmo          #+#    #+#             */
/*   Updated: 2021/03/20 00:58:28 by snorthmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void	philo_eating(int i)
{
	sem_wait(g_sem);
	sem_wait(g_struct.print_sem);
	printf("%ld %i has taken a fork\n", subtract_time(g_struct.start_time), \
	i + 1);
	sem_post(g_struct.print_sem);
	sem_wait(g_sem);
	sem_wait(g_struct.print_sem);
	printf("%ld %i has taken a fork\n", subtract_time(g_struct.start_time), \
	i + 1);
	sem_post(g_struct.print_sem);
	gettimeofday(&g_philo[i]->last_time_eat, NULL);
	sem_wait(g_struct.print_sem);
	printf("%ld %i is eating\n", subtract_time(g_struct.start_time), i + 1);
	sem_post(g_struct.print_sem);
	usleep(g_struct.time_to_eat);
	sem_post(g_sem);
	sem_post(g_sem);
	g_philo[i]->times_eat++;
	if (g_philo[i]->times_eat == g_struct.num_to_eat)
		sem_post(g_full);
}
