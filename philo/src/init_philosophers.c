/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philosophers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hali-mah <hali-mah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 21:48:44 by hali-mah          #+#    #+#             */
/*   Updated: 2025/01/10 21:22:07 by hali-mah         ###   ########.fr       */
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
