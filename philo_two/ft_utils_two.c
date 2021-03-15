/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snorthmo <snorthmo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 13:15:45 by snorthmo          #+#    #+#             */
/*   Updated: 2021/03/10 16:18:08 by snorthmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

long	subtract_time(struct timeval eat_last)
{
	struct timeval	current;
	struct timeval	tmp;

	gettimeofday(&current, NULL);
	tmp.tv_sec = current.tv_sec - eat_last.tv_sec;
	tmp.tv_usec = current.tv_usec - eat_last.tv_usec;
	if (tmp.tv_usec < 0)
	{
		tmp.tv_sec--;
		tmp.tv_usec += 1000000;
	}
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

int		ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

int		print_error(char *str, int ret)
{
	printf("%s", str);
	return (ret);
}
