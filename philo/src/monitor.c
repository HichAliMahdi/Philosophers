/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hali-mah <hali-mah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 22:58:04 by hali-mah          #+#    #+#             */
/*   Updated: 2025/01/13 16:16:09 by hali-mah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static int	check_all_philosophers_ate(t_table *table)
{
	int	i;
	int	all_ate;

	if (table->max_meals == -1)
		return (0);
	pthread_mutex_lock(&table->state_lock);
	i = 0;
	all_ate = 1;
	while (i < table->num_philosophers)
	{
		if (table->philosophers[i].meals_eaten < table->max_meals)
			all_ate = 0;
		i++;
	}
	if (all_ate)
		table->simulation_running = 0;
	pthread_mutex_unlock(&table->state_lock);
	return (all_ate);
}

static int	check_philosopher_death(t_table *table, int i)
{
	long	time_since_last_meal;

	pthread_mutex_lock(&table->state_lock);
	time_since_last_meal = current_time()
		- table->philosophers[i].times.last_meal;
	if (time_since_last_meal > table->philosophers[i].times.die
		&& table->simulation_running)
	{
		printf("%ld %d died\n",
			current_time() - table->philosophers[i].times.born_time,
			table->philosophers[i].id);
		table->simulation_running = 0;
		pthread_mutex_unlock(&table->state_lock);
		return (1);
	}
	pthread_mutex_unlock(&table->state_lock);
	return (0);
}

int	check_simulation_status(t_table *table)
{
	int	status;

	pthread_mutex_lock(&table->state_lock);
	status = table->simulation_running;
	pthread_mutex_unlock(&table->state_lock);
	return (status);
}

void	*monitor_philosophers(void *arg)
{
	t_table	*table;
	int		i;

	table = (t_table *)arg;
	while (check_simulation_status(table))
	{
		if (check_all_philosophers_ate(table))
			break ;
		i = 0;
		while (i < table->num_philosophers)
		{
			if (check_philosopher_death(table, i))
				return (NULL);
			i++;
		}
		usleep(1000);
	}
	return (NULL);
}
