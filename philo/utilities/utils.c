/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hali-mah <hali-mah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 21:58:17 by hali-mah          #+#    #+#             */
/*   Updated: 2025/01/10 21:06:16 by hali-mah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

long	current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	precise_usleep(int ms)
{
	struct timespec	start;
	struct timespec	current;
	long			elapsed_ms;

	clock_gettime(CLOCK_MONOTONIC, &start);
	while (1)
	{
		clock_gettime(CLOCK_MONOTONIC, &current);
		elapsed_ms = (current.tv_sec - start.tv_sec) * 1000
			+ (current.tv_nsec - start.tv_nsec) / 1000000;
		if (elapsed_ms >= ms)
			break ;
		usleep(500);
	}
}

long	ft_strtol(const char *str, int *error)
{
	char	*endptr;
	long	val;

	errno = 0;
	val = strtol(str, &endptr, 10);
	if ((errno == ERANGE && (val == LONG_MAX || val == LONG_MIN))
		|| (errno != 0 && val == 0))
	{
		*error = 1;
		return (0);
	}
	if (endptr == str || *endptr != '\0')
	{
		*error = 1;
		return (0);
	}
	*error = 0;
	return (val);
}

int	validate_numeric_input(const char *str)
{
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (0);
		str++;
	}
	return (1);
}
