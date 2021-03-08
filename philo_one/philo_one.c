/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snorthmo <snorthmo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 12:25:01 by snorthmo          #+#    #+#             */
/*   Updated: 2021/03/08 15:30:00 by snorthmo         ###   ########.fr       */
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
			break ;
		usleep(500);
	}
	g_struct.queue = ((i + 2) >= g_struct.p_num) ? 1 : (g_struct.queue + 2);
	while (1)
	{
		philo_eating(i);
		pthread_mutex_lock(&g_struct.print_mutex);
		printf("%ld %i is sleeping\n", subtract_time(g_struct.start_time), \
		i + 1);
		pthread_mutex_unlock(&g_struct.print_mutex);
		usleep(g_struct.time_to_sleep);
		pthread_mutex_lock(&g_struct.print_mutex);
		printf("%ld %i is thinking\n", subtract_time(g_struct.start_time), \
		i + 1);
		pthread_mutex_unlock(&g_struct.print_mutex);
	}
	return (NULL);
}

void	*check_death(void *ptr)
{
	int				i;

	while (1)
	{
		i = 0;
		while (i < g_struct.p_num)
		{
			pthread_mutex_lock(&g_philo[i]->eat_mutex);
			if (subtract_time(g_philo[i]->last_time_eat) > \
			g_struct.time_to_die)
			{
				pthread_mutex_lock(&g_struct.print_mutex);
				printf("%ld %i died\n", subtract_time(g_struct.start_time), \
				i + 1);
				return (NULL);
			}
			pthread_mutex_unlock(&g_philo[i]->eat_mutex);
			i++;
		}
		if (g_struct.full_philos == g_struct.p_num)
			return (NULL);
	}
	return (ptr);
}

int		check_input(int argc, char **argv)
{
	int		i;
	int		j;
	int		res;

	if (argc != 5 && argc != 6)
		return (print_error("ERROR: Wrong number of arguments\n", -1));
	j = 1;
	res = -1;
	while (j < argc)
	{
		i = 0;
		while ((res = ft_isdigit(argv[j][i])) == 1)
			i++;
		if (res == 0 && argv[j][i] != '\0')
			return (print_error("ERROR: The arguments are numbers\n", -1));
		j++;
	}
	return (0);
}

int		main(int argc, char **argv)
{
	int			i;

	if (check_input(argc, argv) == -1)
		return (1);
	g_struct = init_struct(argv);
	if (init_all_philo() == -1)
		return (1);
	pthread_create(&g_struct.check_death, NULL, check_death, NULL);
	i = 0;
	while (i < g_struct.p_num)
	{
		pthread_create(g_thread[i], NULL, philo_doing_smth, &g_philo[i]->p_i);
		i++;
	}
	pthread_join(g_struct.check_death, NULL);
	free_all();
	return (0);
}
