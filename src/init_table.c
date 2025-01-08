/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hali-mah <hali-mah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 21:26:40 by hali-mah          #+#    #+#             */
/*   Updated: 2025/01/08 21:47:25 by hali-mah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	parse_args(t_table *table, int argc, char **argv)
{
	table->num_philosophers = ft_atoi(argv[1]);
	table->time_to_die = ft_atoi(argv[2]);
	table->time_to_eat = ft_atoi(argv[3]);
	table->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		table->max_meals = ft_atoi(argv[5]);
	else
		table->max_meals = -1;
	table->simulation_running = 1;
	table->start_time = current_time();
	return (0);
}

int	init_table_resources(t_table *table)
{
	int	i;

	i = 0;
	table->forks = malloc(sizeof(pthread_mutex_t) * table->num_philosophers);
	if (!table->forks || !table->philosophers)
		return (1);
	while (i < table->num_philosophers)
	{
		pthread_mutex_init(&table->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&table->print_lock, NULL);
	return (0);
}

int	init_table(t_table *table, int argc, char **argv)
{
	if (parse_args(table, argc, argv))
		return (1);
	if (init_table_resources(table))
		return (1);
	return (0);
}
