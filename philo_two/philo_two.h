/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_two.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snorthmo <snorthmo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 13:03:36 by snorthmo          #+#    #+#             */
/*   Updated: 2021/03/17 16:43:52 by snorthmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_TWO_H
# define PHILO_TWO_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <string.h>
# include <semaphore.h>
# include <fcntl.h>
# include <sys/stat.h>

typedef struct		s_struct
{
	int				p_num;
	long			time_to_eat;
	long			time_to_sleep;
	long			time_to_die;
	int				num_to_eat;
	struct timeval	start_time;
	int				full_philos;
	sem_t			*print_sem;
	pthread_t		check_death;
}					t_struct;

typedef struct		s_philo
{
	struct timeval	last_time_eat;
	int				times_eat;
	int				queue;
	int				p_i;
}					t_philo;

int					ft_atoi(const char *str);
t_struct			init_struct(char **argv);
int					init_all_philo(void);
void				*check_death(void *ptr);
char				*free_all(void);
void				philo_eating(int i);
long				subtract_time(struct timeval eat_last);
int					print_error(char *str, int ret);
int					ft_isdigit(int c);

t_struct			g_struct;
t_philo				**g_philo;
pthread_t			**g_thread;
sem_t				*g_sem;

#endif
