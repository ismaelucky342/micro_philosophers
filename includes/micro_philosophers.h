#ifndef MINI_PHILOSOPHERS_H
#define MINI_PHILOSOPHERS_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <pthread.h>
#include <semaphore.h>
#include <string.h>
#include <fcntl.h>
#include <signal.h>

typedef struct s_philo {
    int index;
    long last_meal_time;
    int meal_count;
} t_philo;

typedef struct s_arg {
    int num_philos;
    long time_to_die;
    long time_to_eat;
    long time_to_sleep;
    int num_meals;
    pid_t *pids;
    t_philo philo;
    long start_time;
    sem_t *forks;
    sem_t *write_lock;
    sem_t *stop;
    sem_t *meals_done;
    pthread_t monitor_thread;
} t_arg;


// Color definitions
#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"

// Function prototypes
long current_time(void);
void print_usage(void);
void take_forks_and_eat(t_arg *args);
void sleep_and_think(t_arg *args);
void *philosopher_routine(void *arg);
void *monitor_meals(void *arg);
void *monitor_death(void *arg);
void init_semaphores(t_arg *args);
void init_monitor(t_arg *args);
void init_philosopher(t_arg *args);
void init_args(t_arg *args, int argc, char **argv);
void start_philosophers(t_arg *args);
void cleanup(t_arg *args);

#endif // MINI_PHILOSOPHERS_H