/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snorthmo <snorthmo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 12:25:01 by snorthmo          #+#    #+#             */
/*   Updated: 2021/03/21 10:10:56 by snorthmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void	*philo_doing_smth(void *num)
{
	int			i;
	pthread_t	death;

	i = *(int *)num;
	pthread_create(&death, NULL, check_death, num);
	while (!g_philo[i]->death_flag)
	{
		philo_eating(i);
		sem_wait(g_struct.print_sem);
		printf("%ld %i is sleeping\n", subtract_time(g_struct.start_time), \
		i + 1);
		sem_post(g_struct.print_sem);
		usleep(g_struct.time_to_sleep);
		sem_wait(g_struct.print_sem);
		printf("%ld %i is thinking\n", subtract_time(g_struct.start_time), \
		i + 1);
		sem_post(g_struct.print_sem);
	}
	pthread_join(death, NULL);
	exit(0);
}

void	*check_death(void *num)
{
	int		i;

	i = *(int *)num;
	while (!g_philo[i]->death_flag)
	{
		if (subtract_time(g_philo[i]->last_time_eat) > g_struct.time_to_die)
		{
			sem_wait(g_struct.print_sem);
			printf("%ld %i died\n", subtract_time(g_struct.start_time), \
			i + 1);
			g_philo[i]->death_flag = 1;
		}
	}
	exit(0);
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

int		parent_process(void)
{
	int		i;
	pid_t	full;

	i = 0;
	full = fork();
	if (full == 0)
		check_full();
	else if (full > 0)
	{
		while (i < g_struct.p_num)
		{
			g_pid[i] = fork();
			if (g_pid[i] == 0)
				philo_doing_smth(&g_philo[i]->p_i);
			if (g_pid[i] < 0)
				return (print_error("process ended with mistake\n", errno));
			i++;
		}
	}
	else
		return (print_error("ERROR: process ended with a mistake\n", errno));
	waitpid(-1, NULL, 0);
	kill_all();
	exit(0);
}

int		main(int argc, char **argv)
{
	pid_t		pid;

	if (check_input(argc, argv) == -1)
		return (1);
	g_struct = init_struct(argv);
	if (init_all_philo() == -1)
		return (1);
	pid = fork();
	if (pid == 0)
		parent_process();
	else if (pid > 0)
		waitpid(-1, NULL, 0);
	else
		return (print_error("ERROR: the process ended with a mistake", errno));
	free_all();
	return (0);
}
