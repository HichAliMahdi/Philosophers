/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hali-mah <hali-mah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 22:11:10 by hali-mah          #+#    #+#             */
/*   Updated: 2025/01/08 22:26:36 by hali-mah         ###   ########.fr       */
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
