/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hali-mah <hali-mah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 21:17:35 by hali-mah          #+#    #+#             */
/*   Updated: 2025/04/04 11:08:55 by hali-mah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	main(int argc, char **argv)
{
	t_table	table;

	if (argc < 5 || argc > 6)
	{
		printf("Usage: ./philosophers num_philosophers time_to_die "
			"time_to_eat time_to_sleep [max_meals]\n");
		return (1);
	}
	if (init_table(&table, argc, argv))
	{
		printf("Error: Invalid arguments or initialization failed\n");
		return (1);
	}
	start_simulation(&table);
	cleanup(&table);
	return (0);
}
