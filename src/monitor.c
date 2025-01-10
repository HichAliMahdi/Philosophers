/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hali-mah <hali-mah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 21:20:26 by hali-mah          #+#    #+#             */
/*   Updated: 2025/01/10 21:29:00 by hali-mah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	check_all_philosophers_satisfied(t_table *table)
{
	int	i;
	int	all_satisfied;

	if (table->max_meals == -1)
		return (0);
	pthread_mutex_lock(&table->state_lock);
	all_satisfied = 1;
	i = 0;
	while (i < table->num_philosophers)
	{
		if (table->philosophers[i].meals_eaten < table->max_meals)
		{
			all_satisfied = 0;
			break ;
		}
		i++;
	}
	pthread_mutex_unlock(&table->state_lock);
	return (all_satisfied);
}

static void	check_philosopher_status(t_table *table, int i)
{
	long	current;

	pthread_mutex_lock(&table->state_lock);
	current = current_time();
	if (current - table->philosophers[i].last_meal_time > table->time_to_die)
	{
		pthread_mutex_lock(&table->print_lock);
		if (table->simulation_running)
		{
			printf("%ld %d died\n", current - table->start_time,
				table->philosophers[i].id);
			table->simulation_running = 0;
		}
		pthread_mutex_unlock(&table->print_lock);
	}
	pthread_mutex_unlock(&table->state_lock);
}

void	*monitor_philosophers(void *arg)
{
	t_table	*table;
	int		i;

	table = (t_table *)arg;
	while (table->simulation_running
		&& !check_all_philosophers_satisfied(table))
	{
		i = 0;
		while (i < table->num_philosophers)
		{
			check_philosopher_status(table, i);
			if (!table->simulation_running)
				break ;
			i++;
		}
		usleep(1000);
	}
	pthread_mutex_lock(&table->state_lock);
	table->simulation_running = 0;
	pthread_mutex_unlock(&table->state_lock);
	return (NULL);
}
