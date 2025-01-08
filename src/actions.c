/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hali-mah <hali-mah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 22:20:56 by hali-mah          #+#    #+#             */
/*   Updated: 2025/01/08 22:26:36 by hali-mah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	print_action(t_philosopher *philosopher, const char *action)
{
	t_table	table;

	table = philosopher->table;
	pthread_mutex_lock(&table->print_lock);
	if (table->simulation_running)
		printf("%ld %d %s\n", current_time() - table->start_time,
			philosopher->id, action);
	pthread_mutex_unlock(&table->print_lock);
}
