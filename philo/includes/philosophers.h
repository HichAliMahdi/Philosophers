/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hali-mah <hali-mah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 11:52:32 by hali-mah          #+#    #+#             */
/*   Updated: 2025/01/13 16:07:56 by hali-mah         ###   ########.fr       */
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

typedef struct timeval	t_timeval;

typedef struct s_times
{
	int		die;
	int		eat;
	int		sleep;
	long	last_meal;
	long	born_time;
}	t_times;

typedef struct s_philosopher
{
	int				id;
	t_times			times;
	int				meals_eaten;
	int				must_eat;
	int				philo_count;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
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
	pthread_mutex_t	meal_lock;
	t_philosopher	*philosophers;
	long			start_time;
}	t_table;

// Function prototypes
int		ft_atoi(const char *str);
size_t	current_time(void);
void	precise_usleep(size_t ms);
int		parse_args(t_table *table, int argc, char **argv);
int		init_table_resources(t_table *table);
int		init_table(t_table *table, int argc, char **argv);
void	setup_philosopher(t_philosopher *philosopher, t_table *table, int i);
int		init_philosophers(t_table *table);
void	*monitor_philosophers(void *arg);
void	destroy_mutexes(t_table *table);
void	cleanup(t_table *table);
int		check_simulation_status(t_table *table);
void	*philosopher_routine(void *arg);
void	start_simulation(t_table *table);
void	print_action(t_philosopher *philosopher, const char *action);
void	take_forks(t_philosopher *philosopher);
void	eat(t_philosopher *philosopher);
void	put_forks(t_philosopher *philosopher);

#endif