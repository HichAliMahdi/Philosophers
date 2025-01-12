/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hali-mah <hali-mah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 22:04:01 by hali-mah          #+#    #+#             */
/*   Updated: 2025/01/10 18:42:55 by hali-mah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	destroy_mutexes(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->num_philosophers)
	{
		pthread_mutex_destroy(&table->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&table->print_lock);
	pthread_mutex_destroy(&table->state_lock);
}

void	cleanup(t_table *table)
{
	destroy_mutexes(table);
	if (table->forks)
		free(table->forks);
	if (table->philosophers)
		free(table->philosophers);
}
