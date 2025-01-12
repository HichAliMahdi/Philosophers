/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hali-mah <hali-mah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 11:52:32 by hali-mah          #+#    #+#             */
/*   Updated: 2025/01/10 21:24:57 by hali-mah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <string.h>
# include <limits.h>
# include <errno.h>

typedef enum e_philo_state
{
	THINKING,
	HUNGRY,
	EATING,
	SLEEPING
}	t_philo_state;

typedef struct s_stats
{
	long			total_meals;
	long			longest_meal_wait;
	long			total_think_time;
	long			total_sleep_time;
	pthread_mutex_t	stats_mutex;
}	t_stats;

typedef struct s_philosopher
{
	int				id;
	long			last_meal_time;
	int				meals_eaten;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	state_mutex;
	t_philo_state	state;
	struct s_table	*table;
}	t_philosopher;

typedef struct s_table
{
	int				num_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				max_meals;
	int				simulation_running;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	state_lock;
	t_philosopher	*philosophers;
	long			start_time;
	t_stats			stats;
}	t_table;

// Function prototypes
int		ft_atoi(const char *str);
long	current_time(void);
void	precise_usleep(int ms);
int		parse_args(t_table *table, int argc, char **argv);
int		init_table_resources(t_table *table);
int		init_table(t_table *table, int argc, char **argv);
void	setup_philosopher(t_philosopher *philosopher, t_table *table, int i);
int		init_philosophers(t_table *table);
int		check_all_philosophers_satisfied(t_table *table);
void	*monitor_philosophers(void *arg);
void	destroy_mutexes(t_table *table);
void	cleanup(t_table *table);
void	*philosopher_routine(void *arg);
void	start_simulation(t_table *table);
void	print_action(t_philosopher *philosopher, const char *action);
void	take_forks(t_philosopher *philosopher);
void	eat(t_philosopher *philosopher);
void	put_forks(t_philosopher *philosopher);
long	ft_strtol(const char *str, int *error);
int		validate_numeric_input(const char *str);
void	init_stats(t_stats *stats);
void	update_stats(t_philosopher *philo,
			t_philo_state new_state, long duration);
void	print_final_stats(t_table *table);

#endif