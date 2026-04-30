/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasanche <dasanche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 16:59:00 by dasanche          #+#    #+#             */
/*   Updated: 2026/03/17 18:52:56 by dasanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <limits.h>
# include <string.h>

// ESTRUCTURAS:

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	long long		last_meal_time;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	struct s_table	*table;
}	t_philo;

typedef struct s_table
{
	int				num_philos;
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
	int				must_eat_count;
	long long		start_time;
	int				someone_died;
	pthread_mutex_t	*forks;
	pthread_mutex_t	death_lock;
	pthread_mutex_t	meal_lock;
	t_philo			*philos;
	pthread_t		monitor_thread;
	int				death_lock_init;
	int				meal_lock_init;
	int				forks_init_count;
}	t_table;

// PROTOTIPOS/FIRMAS:

// Parsing
t_table		*parse_arguments(int argc, char **argv);
int			ft_atoi(const char *str);
int			ft_isdigit(int c);
int			ft_isspace(int c);
int			validate_and_skip_prefix(const char *str, int *i);
long long	convert_digits(const char *str, int *i);

// Init
int			init_mutexes(t_table *table);
int			init_forks(t_table *table);
int			init_philos(t_table *table);

// Time
long long	get_time_ms(void);
long long	elapsed_time(t_table *table);
void		precise_sleep(long long ms);

// Threads
int			start_simulation(t_table *table);

// Philosophers
void		*philosopher_routine(void *arg);
void		take_forks(t_philo *philo);
void		drop_forks(t_philo *philo);
void		philo_eat(t_philo *philo);
int			check_philosopher_death(t_philo *philo);
int			check_must_eat_limit(t_philo *philo);

// Monitor
void		*monitor_routine(void *arg);
int			check_deaths(t_table *table);
int			check_all_ate(t_table *table);

// Print
void		print_action(t_philo *philo, const char *action);
void		print_death(t_philo *philo);
void		philo_think(t_philo *philo);
void		philo_sleep(t_philo *philo);

// Cleanup
void		cleanup(t_table *table);
void		destroy_mutexes(t_table *table);

// Utils
void		print_error(char *message);
int			ft_strlen(const char *str);
char		*ft_strcpy(char *dest, const char *src);
int			ft_strcpy_offset(char *dest, const char *src, int offset);
void		reverse_str_range(char *str, int start, int end);
int			ft_itoa(int n, char *str);
int			ft_lltoa(long long n, char *str);
#endif
