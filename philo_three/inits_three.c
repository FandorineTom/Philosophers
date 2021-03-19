/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits_three.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snorthmo <snorthmo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 13:45:01 by snorthmo          #+#    #+#             */
/*   Updated: 2021/03/20 00:43:47 by snorthmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

t_struct	init_struct(char **argv)
{
	t_struct	struct_p;

	memset(&struct_p, 0, sizeof(t_struct));
	struct_p.p_num = ft_atoi(argv[1]);
	struct_p.time_to_eat = ft_atoi(argv[3]) * 1000;
	struct_p.time_to_sleep = ft_atoi(argv[4]) * 1000;
	struct_p.time_to_die = ft_atoi(argv[2]);
	if (argv[5])
		struct_p.num_to_eat = ft_atoi(argv[5]);
	return (struct_p);
}

int			init_g_philo(void)
{
	int		i;

	i = 0;
	while (i < g_struct.p_num)
	{
		memset(g_philo[i], 0, sizeof(t_philo));
		g_philo[i]->last_time_eat = g_struct.start_time;
		g_philo[i]->p_i = i;
		i++;
	}
	sem_unlink("/print_sem");
	sem_unlink("/fork_sem");
	sem_unlink("/full_sem");
	if ((g_sem = sem_open("/fork_sem", O_CREAT, 0666, g_struct.p_num))\
	== SEM_FAILED || (g_struct.print_sem = sem_open("/print_sem", O_CREAT,\
	0666, 1)) == SEM_FAILED || (g_full = sem_open("/full_sem", O_CREAT, 0666,\
	0)) == SEM_FAILED)
		return (print_error("ERROR: couldn't create semaphore\n", -1));
	return (0);
}

int			init_all_philo(void)
{
	int		i;

	if (!(g_philo = (t_philo **)malloc(sizeof(t_philo *) * g_struct.p_num))\
	|| !(g_pid = (pid_t *)malloc(sizeof(pid_t) * g_struct.p_num)))
		return (print_error("ERROR: malloc error\n", -1));
	i = 0;
	while (i < g_struct.p_num)
	{
		if (!(g_philo[i] = (t_philo *)malloc(sizeof(t_philo))))
			return (print_error("ERROR: malloc error\n", -1));
		i++;
	}
	gettimeofday(&g_struct.start_time, NULL);
	init_g_philo();
	return (0);
}

char		*free_all(void)
{
	int	i;

	i = 0;
	while (i < g_struct.p_num)
		free(g_philo[i++]);
	free(g_philo);
	free(g_pid);
	return (NULL);
}

void		check_full(void)
{
	int		i;

	i = 0;
	while (i < g_struct.p_num)
	{
		sem_wait(g_full);
		i++;
	}
	exit(0);
}
