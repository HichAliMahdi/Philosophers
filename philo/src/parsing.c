/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hali-mah <hali-mah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 21:29:53 by hali-mah          #+#    #+#             */
/*   Updated: 2025/01/10 21:36:49 by hali-mah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static int	validate_and_parse_int(char *arg, int *out_value)
{
	int	error;

	if (!validate_numeric_input(arg))
		return (1);
	*out_value = ft_strtol(arg, &error);
	if (error)
		return (1);
	return (0);
}

static int	validate_arguments(t_table *table, int argc, char **argv)
{
	if (table->num_philosophers <= 0 || table->num_philosophers > 200
		|| table->time_to_die <= 0 || table->time_to_eat <= 0
		|| table->time_to_sleep <= 0)
	{
		printf("Error: Invalid argument values\n");
		return (1);
	}
	if (argc == 6)
	{
		if (validate_and_parse_int(argv[5],
				&table->max_meals) || table->max_meals <= 0)
			return (1);
	}
	else
		table->max_meals = -1;
	return (0);
}

int	parse_args(t_table *table, int argc, char **argv)
{
	if (validate_and_parse_int(argv[1], &table->num_philosophers)
		|| validate_and_parse_int(argv[2], &table->time_to_die)
		|| validate_and_parse_int(argv[3], &table->time_to_eat)
		|| validate_and_parse_int(argv[4], &table->time_to_sleep))
	{
		return (1);
	}
	if (validate_arguments(table, argc, argv))
		return (1);
	table->simulation_running = 1;
	table->start_time = current_time();
	init_stats(&table->stats);
	return (0);
}
