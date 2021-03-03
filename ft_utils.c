/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snorthmo <snorthmo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 13:15:45 by snorthmo          #+#    #+#             */
/*   Updated: 2021/03/04 00:20:15 by snorthmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

long	subtract_time(struct timeval *eat_last, char flag)
{
	struct timeval	current;
	struct timeval	tmp;

	gettimeofday(&current, NULL);
	if (flag == 'd')
	{
		timersub(&current, eat_last, &tmp);
		// tmp.tv_sec = current.tv_sec - g_philo[i]->last_time_eat.tv_sec;
		// tmp.tv_usec = current.tv_usec - g_philo[i]->last_time_eat.tv_usec;
		// printf("\t\t\t\t\t\t\t\t\ttv_sec %ld\n", current.tv_sec);
		// printf("\t\t\t\t\t\t\t\t\ttv_usec %d\n", current.tv_usec);
	}
	else
	{
		timersub(&current, eat_last, &tmp);
		// tmp.tv_sec = current.tv_sec - g_struct.start_time.tv_sec;
		// tmp.tv_usec = current.tv_usec - g_struct.start_time.tv_usec;
	}
	// if (tmp.tv_usec < 0)
	// {
    //     tmp.tv_sec--;
	// 	tmp.tv_usec += 1000000;
	// }
	// if (flag == 'd')
	// 	printf("\t\t\t\t\t\t\t\t\tbefore %ld\n", tmp.tv_sec * 1000 + tmp.tv_usec / 1000);
	return (tmp.tv_sec * 1000 + tmp.tv_usec / 1000);
}

int		ft_atoi(const char *str)
{
	long	result;
	long	result_tempo;
	int		negative;

	result = 0;
	negative = 1;
	while (*str && (*str == '\t' || *str == '\r' || *str == ' '\
			|| *str == '\f' || *str == '\v' || *str == '\n'))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			negative = -1;
		str++;
	}
	while ((*str >= '0') && (*str <= '9'))
	{
		result_tempo = result;
		result = result * 10 + (*str - '0');
		str++;
		if (result_tempo > result)
			return (negative == 1 ? -1 : 0);
	}
	return (result * negative);
}