/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hali-mah <hali-mah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 22:20:56 by hali-mah          #+#    #+#             */
/*   Updated: 2025/01/08 22:49:28 by hali-mah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	print_action(t_philosopher *philosopher, const char *action)
{
	t_table	table;

	table = philosopher->table;
	pthread_mutex_lock(&table->print_lock);
	if (table->simulation_running)
		printf("%ld %d %s\n", current_time() - table->start_time,
			philosopher->id, action);
	pthread_mutex_unlock(&table->print_lock);
}

void	take_forks(t_philosopher *philosopher)
{
	pthread_mutex_lock(philosopher->left_fork);
	print_action(philosopher, "has taken a fork");
	pthread_mutex_lock(philosopher->right_fork);
	print_action(philosopher, "has taken a fork");
}

void	eat(t_philosopher *philosopher)
{
	t_table	*table;

	table = philosopher->table;
	print_action(philosopher, "is eating");
	philosopher->last_meal_time = current_time();
	philosopher->meals_eaten++;
	precise_usleep(table->time_to_eat);
}

void	put_forks(t_philosopher	*philosopher)
{
	pthread_mutex_unlock(philosopher->left_fork);
	pthread_mutex_unlock(philosopher->right_fork);
}
