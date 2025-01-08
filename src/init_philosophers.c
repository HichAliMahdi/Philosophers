/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philosophers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hali-mah <hali-mah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 21:48:44 by hali-mah          #+#    #+#             */
/*   Updated: 2025/01/08 23:24:29 by hali-mah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	setup_philosopher(t_philosopher *philosopher, t_table *table, int i)
{
	philosopher->id = i + 1;
	philosopher->meals_eaten = 0;
	philosopher->last_meal_time = table->start_time;
	philosopher->left_fork = &table->forks[i];
	philosopher->right_fork = &table->forks[(i + 1) % table->num_philosophers];
	philosopher->table = table;
}

int	init_philosophers(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->num_philosophers)
	{
		setup_philosopher(&table->philosophers[i], table, i);
		i++;
	}
	return (0);
}
void	*monitor_philosophers(void *arg)
{
	t_table	*table;
	int		i;
	long	current;

	table = (t_table *)arg;
	while (table->simulation_running)
	{
		i = 0;
		while (i < table->num_philosophers)
		{
			current = current_time();
			if (current - table->philosophers[i].last_meal_time > table->time_to_die)
			{
				pthread_mutex_lock(&table->print_lock);
				printf("%ld %d died\n", current - table->start_time,
					table->philosophers[i].id);
				table->simulation_running = 0;
				pthread_mutex_unlock(&table->print_lock);
				return (NULL);
			}
			if (table->max_meals != -1 && 
				table->philosophers[i].meals_eaten >= table->max_meals)
			{
				i++;
				if (i == table->num_philosophers)
				{
					table->simulation_running = 0;
					return (NULL);
				}
				continue ;
			}
			i++;
		}
		usleep(1000);
	}
	return (NULL);
}
