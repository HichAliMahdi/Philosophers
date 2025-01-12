/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hali-mah <hali-mah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 21:26:40 by hali-mah          #+#    #+#             */
/*   Updated: 2025/01/12 19:57:40 by hali-mah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static int	initialize_forks(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->num_philosophers)
	{
		if (pthread_mutex_init(&table->forks[i], NULL) != 0)
		{
			while (--i >= 0)
				pthread_mutex_destroy(&table->forks[i]);
			return (1);
		}
		i++;
	}
	return (0);
}

static int	initialize_locks(t_table *table)
{
	if (pthread_mutex_init(&table->state_lock, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&table->print_lock, NULL) != 0)
	{
		pthread_mutex_destroy(&table->state_lock);
		return (1);
	}
	return (0);
}

int	init_table_resources(t_table *table)
{
	table->forks = malloc(sizeof(pthread_mutex_t) * table->num_philosophers);
	if (!table->forks)
		return (1);
	table->philosophers = malloc(sizeof(t_philosopher)
			* table->num_philosophers);
	if (!table->philosophers)
	{
		free(table->forks);
		return (1);
	}
	if (initialize_locks(table) != 0)
	{
		free(table->forks);
		free(table->philosophers);
		return (1);
	}
	if (initialize_forks(table) != 0)
	{
		pthread_mutex_destroy(&table->print_lock);
		pthread_mutex_destroy(&table->state_lock);
		free(table->forks);
		free(table->philosophers);
		return (1);
	}
	return (0);
}

int	init_table(t_table *table, int argc, char **argv)
{
	printf("Debug: Starting init_table\n");
	if (parse_args(table, argc, argv))
		return (1);
	if (init_table_resources(table))
		return (1);
	if (init_philosophers(table))
		return (1);
	return (0);
}
