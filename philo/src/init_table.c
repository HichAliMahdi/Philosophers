/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hali-mah <hali-mah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 21:26:40 by hali-mah          #+#    #+#             */
/*   Updated: 2025/01/12 20:07:22 by hali-mah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	parse_args(t_table *table, int argc, char **argv)
{
	table->num_philosophers = ft_atoi(argv[1]);
	table->time_to_die = ft_atoi(argv[2]);
	table->time_to_eat = ft_atoi(argv[3]);
	table->time_to_sleep = ft_atoi(argv[4]);
	if (table->num_philosophers <= 0 || table->num_philosophers > 200
		|| table->time_to_die <= 0 || table->time_to_eat <= 0
		|| table->time_to_sleep <= 0)
	{
		printf("Debug: Invalid argument values\n");
		return (1);
	}
	if (argc == 6)
	{
		table->max_meals = ft_atoi(argv[5]);
		if (table->max_meals <= 0)
			return (1);
	}
	else
		table->max_meals = -1;
	table->simulation_running = 1;
	table->start_time = current_time();
	return (0);
}

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
	if (parse_args(table, argc, argv))
		return (1);
	if (init_table_resources(table))
		return (1);
	if (init_philosophers(table))
		return (1);
	return (0);
}
