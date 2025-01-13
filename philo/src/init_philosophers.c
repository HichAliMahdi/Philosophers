/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philosophers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hali-mah <hali-mah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 21:48:44 by hali-mah          #+#    #+#             */
/*   Updated: 2025/01/13 16:11:23 by hali-mah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	setup_philosopher(t_philosopher *philosopher, t_table *table, int i)
{
	philosopher->id = i + 1;
	philosopher->times.die = table->time_to_die;
	philosopher->times.eat = table->time_to_eat;
	philosopher->times.sleep = table->time_to_sleep;
	philosopher->times.last_meal = current_time();
	philosopher->times.born_time = current_time();
	philosopher->meals_eaten = 0;
	philosopher->must_eat = table->max_meals;
	philosopher->philo_count = table->num_philosophers;
	philosopher->left_fork = &table->forks[i];
	if (i == 0)
		philosopher->right_fork = &table->forks[table->num_philosophers - 1];
	else
		philosopher->right_fork = &table->forks[i - 1];
	philosopher->table = table;
}

int	init_philosophers(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->num_philosophers)
	{
		setup_philosopher(&table->philosophers[i], table, i);
	}
	return (0);
}
