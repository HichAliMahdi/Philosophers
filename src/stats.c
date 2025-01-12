/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stats.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hali-mah <hali-mah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 21:07:55 by hali-mah          #+#    #+#             */
/*   Updated: 2025/01/10 21:14:00 by hali-mah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	init_stats(t_stats *stats)
{
	stats->total_meals = 0;
	stats->longest_meal_wait = 0;
	stats->total_think_time = 0;
	stats->total_sleep_time = 0;
	pthread_mutex_init(&stats->stats_mutex, NULL);
}

void	update_stats(t_philosopher *philo,
	t_philo_state new_state, long duration)
{
	t_stats	*stats;

	stats = &philo->table->stats;
	pthread_mutex_lock(&stats->stats_mutex);
	if (new_state == EATING)
	{
		stats->total_meals++;
		if (duration > stats->longest_meal_wait)
			stats->longest_meal_wait = duration;
	}
	else if (new_state == THINKING)
		stats->total_think_time += duration;
	else if (new_state == SLEEPING)
		stats->total_sleep_time += duration;
	pthread_mutex_unlock(&stats->stats_mutex);
}

void	print_final_stats(t_table *table)
{
	t_stats	*stats;
	long	avg_think_time;
	long	avg_sleep_time;

	stats = &table->stats;
	pthread_mutex_lock(&stats->stats_mutex);
	if (table->num_philosophers > 0)
	{
		avg_think_time = stats->total_think_time / table->num_philosophers;
		avg_sleep_time = stats->total_sleep_time / table->num_philosophers;
	}
	else
	{
		avg_think_time = 0;
		avg_sleep_time = 0;
	}
	printf("\n=== Simulation Statistics ===\n");
	printf("Total meals eaten: %ld\n", stats->total_meals);
	printf("Longest wait for a meal: %ld ms\n", stats->longest_meal_wait);
	printf("Average think time per philosopher: %ld ms\n", avg_think_time);
	printf("Average sleep time per philosopher: %ld ms\n", avg_sleep_time);
	pthread_mutex_unlock(&stats->stats_mutex);
}
