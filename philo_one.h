/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snorthmo <snorthmo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 13:03:36 by snorthmo          #+#    #+#             */
/*   Updated: 2021/03/08 13:50:30 by snorthmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <string.h>

typedef struct		s_struct
{
	int				p_num;
	long			time_to_eat;
	long			time_to_sleep;
	long			time_to_die;
	int				num_to_eat;
	struct timeval	start_time;
	int				queue;
	int				full_philos;
	pthread_mutex_t	print_mutex;
	pthread_t		check_death;
	int				time_inited;
}					t_struct;

typedef struct		s_philo
{
	struct timeval	last_time_eat;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	int				times_eat;
	pthread_mutex_t	eat_mutex;
	int				p_i;
}					t_philo;

int					ft_atoi(const char *str);
t_struct			init_struct(char **argv);
int					init_all_philo(void);
char				*free_all(void);
void				philo_eating(int i);
long				subtract_time(struct timeval eat_last, char flag);
int					print_error(char *str, int ret);
int					ft_isdigit(int c);

t_struct			g_struct;
t_philo				**g_philo;
pthread_t			**g_thread;
pthread_mutex_t		**g_mutex;

#endif
