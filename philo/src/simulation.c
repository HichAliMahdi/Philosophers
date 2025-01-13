/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hali-mah <hali-mah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 23:00:21 by hali-mah          #+#    #+#             */
/*   Updated: 2025/01/13 17:18:58 by hali-mah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	initialize_simulation(t_table *table)
{
	int		i;
	long	current;

	current = current_time();
	i = 0;
	while (i < table->num_philosophers)
	{
		table->philosophers[i].times.last_meal = current;
		table->philosophers[i].times.born_time = current;
		i++;
	}
	table->start_time = current;
}

int	handle_thread_creation_failure(t_table *table, int i)
{
	pthread_mutex_lock(&table->state_lock);
	table->simulation_running = 0;
	pthread_mutex_unlock(&table->state_lock);
	while (--i >= 0)
		pthread_join(table->philosophers[i].thread, NULL);
	return (1);
}

int	create_threads(t_table *table, pthread_t *monitor)
{
	int	i;

	i = 0;
	while (i < table->num_philosophers)
	{
		if (pthread_create(&table->philosophers[i].thread, NULL,
				philosopher_routine, &table->philosophers[i]) != 0)
			return (handle_thread_creation_failure(table, i));
		usleep(1000);
		i++;
	}
	if (pthread_create(monitor, NULL, monitor_philosophers, table) != 0)
		return (handle_thread_creation_failure(table, i));
	return (0);
}

void	start_simulation(t_table *table)
{
	pthread_t	monitor;
	int			i;

	initialize_simulation(table);
	if (create_threads(table, &monitor))
		return ;
	pthread_join(monitor, NULL);
	i = 0;
	while (i < table->num_philosophers)
	{
		pthread_join(table->philosophers[i].thread, NULL);
		i++;
	}
}
