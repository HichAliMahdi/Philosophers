/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hali-mah <hali-mah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 22:11:10 by hali-mah          #+#    #+#             */
/*   Updated: 2025/01/13 17:00:45 by hali-mah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	handle_single_philosopher(t_philosopher *philosopher)
{
	t_table	*table;

	table = philosopher->table;
	print_action(philosopher, "has taken a fork");
	precise_usleep(table->time_to_die);
	return (1);
}

void	philosopher_actions(t_philosopher *philosopher)
{
	print_action(philosopher, "is thinking");
	take_forks(philosopher);
	eat(philosopher);
	put_forks(philosopher);
	print_action(philosopher, "is sleeping");
	precise_usleep(philosopher->table->time_to_sleep);
}

void	*philosopher_routine(void *arg)
{
	t_philosopher	*philosopher;
	t_table			*table;

	philosopher = (t_philosopher *)arg;
	table = philosopher->table;
	if (table->num_philosophers == 1)
	{
		handle_single_philosopher(philosopher);
		return (NULL);
	}
	if (philosopher->id % 2)
		usleep(1000);
	while (check_simulation_status(table))
		philosopher_actions(philosopher);
	return (NULL);
}
