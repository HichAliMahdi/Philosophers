/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hali-mah <hali-mah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 22:20:56 by hali-mah          #+#    #+#             */
/*   Updated: 2025/01/12 22:47:03 by hali-mah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	print_action(t_philosopher *philosopher, const char *action)
{
	t_table	*table;

	table = philosopher->table;
	pthread_mutex_lock(&table->print_lock);
	pthread_mutex_lock(&table->state_lock);
	if (table->simulation_running)
	{
		printf("%ld %d %s\n", current_time() - table->start_time,
			philosopher->id, action);
	}
	pthread_mutex_unlock(&table->state_lock);
	pthread_mutex_unlock(&table->print_lock);
}

void	take_forks(t_philosopher *philosopher)
{
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;

	if (philosopher->id % 2 == 0)
	{
		first_fork = philosopher->right_fork;
		second_fork = philosopher->left_fork;
	}
	else
	{
		first_fork = philosopher->left_fork;
		second_fork = philosopher->right_fork;
	}
	pthread_mutex_lock(first_fork);
	print_action(philosopher, "has taken a fork");
	pthread_mutex_lock(second_fork);
	print_action(philosopher, "has taken a fork");
}

void	eat(t_philosopher *philosopher)
{
	t_table	*table;

	table = philosopher->table;
	pthread_mutex_lock(&table->state_lock);
	philosopher->last_meal_time = current_time();
	philosopher->meals_eaten++;
	pthread_mutex_unlock(&table->state_lock);
	print_action(philosopher, "is eating");
	precise_usleep(table->time_to_eat);
}

void	put_forks(t_philosopher *philosopher)
{
	if (philosopher->id % 2)
	{
		pthread_mutex_unlock(philosopher->left_fork);
		pthread_mutex_unlock(philosopher->right_fork);
	}
	else
	{
		pthread_mutex_unlock(philosopher->right_fork);
		pthread_mutex_unlock(philosopher->left_fork);
	}
}
