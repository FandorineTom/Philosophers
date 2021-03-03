/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snorthmo <snorthmo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 12:25:01 by snorthmo          #+#    #+#             */
/*   Updated: 2021/03/04 00:27:19 by snorthmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	*philo_doing_smth(void *num)
{
	int	i;

	i = *(int *)num;
	pthread_detach(*g_thread[i]);
	while (1)
	{
		if (i == g_struct.queue)
			break;
		usleep(500);
	}
	g_struct.queue = ((i + 2) >= g_struct.p_num) ? 1 : (g_struct.queue + 2);
	while (1)
	{
		philo_eating(i);
		printf("%ld__ %i is sleeping\n", subtract_time(&g_struct.start_time, 's'), i + 1);
		usleep(g_struct.time_to_sleep);
		pthread_mutex_lock(&g_struct.print_mutex);
		printf("%ld__ %i is thinking\n", subtract_time(&g_struct.start_time, 's'), i + 1);
		pthread_mutex_unlock(&g_struct.print_mutex);
	}
	return (NULL);
}

void	*check_death(void *ptr)
{
	int				i;
	long tmp;

	while (1)
	{
		i = 0;
		while (i < g_struct.p_num)
		{
			// tmp = subtract_time(g_philo[i]->last_time_eat, 'd');
			// printf("i am here %i\n", i);
			// printf("\t\t\t\t\t\ttmp____after %ld\n", tmp);
			// printf("\t\t\t\t\t\tdie %ld\n", g_struct.time_to_die);
			pthread_mutex_lock(&g_philo[i]->eat_mutex);
			if (subtract_time(&g_philo[i]->last_time_eat, 'd') > g_struct.time_to_die)
			{
				pthread_mutex_lock(&g_struct.print_mutex);
				printf("%ld__ %i DIED DIED DIED DIED DIED DIED DIED DIED DIED\n", subtract_time(&g_philo[i]->last_time_eat, 'd'), i + 1);
				return(NULL);

			}
			pthread_mutex_unlock(&g_philo[i]->eat_mutex);
			i++;
		}
		if (g_struct.num_to_eat && g_struct.full_philos == g_struct.num_to_eat) {
			printf("%ld__ %i DONE DONE DONE DONE DONE DONE DONE DONE DONE\n", subtract_time(&g_struct.start_time, 's'), i + 1); // тут просто надо все очистить и завершить симуляцию? 
			return(NULL);
		}
	}
	return (NULL);
}

int		main(int argc, char **argv)
{
	int			i;

	g_struct = init_struct(argv);
	if (init_all_philo() == 1)
		return (1); //обработать ошибку и еще надо ошибку на печать выводить
	pthread_create(&g_struct.check_death, NULL, check_death, NULL);
	i = 0;
	while (i < g_struct.p_num)
	{
		pthread_create(g_thread[i], NULL, philo_doing_smth, &g_philo[i]->p_i);
		i++;
	}
	i = 0;
	pthread_join(g_struct.check_death, NULL);
	free_all();
	return (0);
}