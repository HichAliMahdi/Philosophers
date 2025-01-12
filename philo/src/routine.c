/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hali-mah <hali-mah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 22:11:10 by hali-mah          #+#    #+#             */
/*   Updated: 2025/01/10 19:38:35 by hali-mah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	*philosopher_routine(void *arg)
{
	t_philosopher	*philosopher;
	t_table			*table;

	philosopher = (t_philosopher *)arg;
	table = philosopher->table;
	while (table->simulation_running)
	{
		print_action(philosopher, "is thinking");
		take_forks(philosopher);
		eat(philosopher);
		put_forks(philosopher);
		print_action(philosopher, "is sleeping");
		precise_usleep(table->time_to_sleep);
	}
	return (NULL);
}

static void	initialize_simulation(t_table *table)
{
	int	i;

	table->start_time = current_time();
	i = 0;
	while (i < table->num_philosophers)
	{
		table->philosophers[i].last_meal_time = table->start_time;
		i++;
	}
}

static int	handle_thread_creation_failure(t_table *table, int i)
{
	pthread_mutex_lock(&table->state_lock);
	table->simulation_running = 0;
	pthread_mutex_unlock(&table->state_lock);
	while (--i >= 0)
		pthread_join(table->philosophers[i].thread, NULL);
	return (1);
}

static int	create_threads(t_table *table, pthread_t *monitor)
{
	int	i;

	i = 0;
	while (i < table->num_philosophers)
	{
		if (pthread_create(&table->philosophers[i].thread, NULL,
				philosopher_routine, &table->philosophers[i]) != 0)
			return (handle_thread_creation_failure(table, i));
		usleep(100);
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
