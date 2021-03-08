/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snorthmo <snorthmo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 13:45:01 by snorthmo          #+#    #+#             */
/*   Updated: 2021/03/08 13:55:02 by snorthmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

t_struct	init_struct(char **argv)
{
	t_struct	struct_p;

	memset(&struct_p, 0, sizeof(t_struct));
	struct_p.p_num = ft_atoi(argv[1]);
	struct_p.time_to_eat = ft_atoi(argv[3]) * 1000;
	struct_p.time_to_sleep = ft_atoi(argv[4]) * 1000;
	struct_p.time_to_die = ft_atoi(argv[2]);
	pthread_mutex_init(&struct_p.print_mutex, NULL);
	if (argv[5])
		struct_p.num_to_eat = ft_atoi(argv[5]);
	return (struct_p);
}

void		init_g_philo(void)
{
	int		i;

	i = 0;
	while (i < g_struct.p_num)
	{
		memset(g_philo[i], 0, sizeof(t_philo));
		g_philo[i]->last_time_eat = g_struct.start_time;
		g_philo[i]->p_i = i;
		if (i == 0)
		{
			g_philo[i]->left_fork = g_mutex[g_struct.p_num - 1];
			g_philo[i]->right_fork = g_mutex[0];
		}
		else
		{
			g_philo[i]->left_fork = g_mutex[i];
			g_philo[i]->right_fork = g_mutex[i - 1];
		}
		pthread_mutex_init(&g_philo[i]->eat_mutex, NULL);
		i++;
	}
}

int			init_all_philo(void)
{
	int		i;

	if (!(g_philo = (t_philo **)malloc(sizeof(t_philo *) * g_struct.p_num)) \
	|| !(g_mutex = (pthread_mutex_t **)malloc(sizeof(pthread_mutex_t *) * \
	g_struct.p_num)) || !(g_thread = (pthread_t **)malloc(sizeof(pthread_t *) \
	* g_struct.p_num)))
		return (print_error("ERROR: malloc error\n", -1));
	i = 0;
	while (i < g_struct.p_num)
	{
		if (!(g_philo[i] = (t_philo *)malloc(sizeof(t_philo) * g_struct.p_num))\
		|| !(g_mutex[i] = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * \
		g_struct.p_num)) || !(g_thread[i] = (pthread_t *)malloc(\
		sizeof(pthread_t) * g_struct.p_num)))
			return (print_error("ERROR: malloc error\n", -1));
		pthread_mutex_init(g_mutex[i], NULL);
		i++;
	}
	gettimeofday(&g_struct.start_time, NULL);
	init_g_philo();
	return (0);
}

char		*free_all(void)
{
	int	i;
	int	total;

	i = 0;
	total = g_struct.p_num;
	while (i < total)
	{
		pthread_mutex_destroy(g_mutex[i]);
		pthread_mutex_destroy(&(g_philo[i]->eat_mutex));
		free(g_philo[i]);
		free(g_mutex[i]);
		free(g_thread[i]);
		i++;
	}
	free(g_philo);
	free(g_mutex);
	free(g_thread);
	pthread_mutex_destroy(&g_struct.print_mutex);
	return (NULL);
}
