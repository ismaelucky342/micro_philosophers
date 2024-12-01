#include "../includes/micro_philosophers.h"

// Main function: Entrada principal del programa. Valida los argumentos y comienza la ejecución de los filósofos.
int main(int argc, char **argv) {
    if (argc != 5 && argc != 6) {
        print_usage();
        return 1;
    }
    t_arg args;
    init_args(&args, argc, argv);
    start_philosophers(&args);
    cleanup(&args);
    return 0;
}
// Main function: Entrada principal del programa. Valida los argumentos y comienza la ejecución de los filósofos.
long current_time(void) {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return 1000 * tv.tv_sec + tv.tv_usec / 1000;
}
// print_usage: Imprime cómo debe ser utilizada la aplicación.
void print_usage(void) {
    printf("Usage: ./philosophers [num_philos] [time_to_die] [time_to_eat] [time_to_sleep] [num_meals]\n");
}
// take_forks_and_eat: Función que simula el comportamiento de un filósofo tomando los tenedores y comiendo.
void take_forks_and_eat(t_arg *args) {
    sem_wait(args->forks);
    sem_wait(args->forks);
    sem_wait(args->write_lock);
    printf(GREEN "%ld philo[%d] has taken a fork\n" RESET, current_time() - args->start_time, args->philo.index + 1);
    printf(GREEN "%ld philo[%d] is eating\n" RESET, current_time() - args->start_time, args->philo.index + 1);
    sem_post(args->write_lock);
    args->philo.last_meal_time = current_time();
    args->philo.meal_count++;
    if (args->philo.meal_count == args->num_meals)
        sem_post(args->meals_done);
    usleep(args->time_to_eat * 1000);
    sem_post(args->forks);
    sem_post(args->forks);
}

// sleep_and_think: Función que simula el comportamiento de un filósofo durmiendo y pensando.
void sleep_and_think(t_arg *args) {
    sem_wait(args->write_lock);
    printf(BLUE "%ld philo[%d] is sleeping\n" RESET, current_time() - args->start_time, args->philo.index + 1);
    sem_post(args->write_lock);
    usleep(args->time_to_sleep * 1000);
    sem_wait(args->write_lock);
    printf(CYAN "%ld philo[%d] is thinking\n" RESET, current_time() - args->start_time, args->philo.index + 1);
    sem_post(args->write_lock);
}
// philosopher_routine: Función que define el ciclo de vida de cada filósofo: comer y pensar.
void *philosopher_routine(void *arg) {
    t_arg *args = (t_arg *)arg;
    args->start_time = current_time();
    while (1) {
        take_forks_and_eat(args);
        sleep_and_think(args);
    }
    return NULL;
}
// monitor_meals: Monitoriza el estado de las comidas de los filósofos, esperando que todos terminen.
void *monitor_meals(void *arg) {
    t_arg *args = (t_arg *)arg;
    for (int i = 0; i < args->num_philos; i++) {
        sem_wait(args->meals_done);
    }
    sem_post(args->stop);
    return NULL;
}

// monitor_death: Monitoriza el estado de muerte de los filósofos, verificando si algún filósofo ha muerto por inanición.
void *monitor_death(void *arg) {
    t_arg *args = (t_arg *)arg;
    while (1) {
        if (current_time() - args->philo.last_meal_time > args->time_to_die) {
            sem_wait(args->write_lock);
            printf(RED "%ld philo[%d] died\n" RESET, current_time() - args->start_time, args->philo.index + 1);
            sem_post(args->stop);
            exit(0);
        }
    }
    return NULL;
}
// init_semaphores: Inicializa los semáforos utilizados para sincronizar a los filósofos.
void init_semaphores(t_arg *args) {
    sem_unlink("forks");
    sem_unlink("write_lock");
    sem_unlink("stop");
    sem_unlink("meals_done");
    args->forks = sem_open("forks", O_CREAT, 0644, args->num_philos);
    args->write_lock = sem_open("write_lock", O_CREAT, 0644, 1);
    args->stop = sem_open("stop", O_CREAT, 0644, 0);
    args->meals_done = sem_open("meals_done", O_CREAT, 0644, 0);
}
// init_monitor: Inicializa el monitor de las comidas si el número de comidas es mayor que cero.
void init_monitor(t_arg *args) {
    if (args->num_meals > 0) {
        pthread_create(&args->monitor_thread, NULL, monitor_meals, args);
        pthread_detach(args->monitor_thread);
    }
}

// init_philosopher: Inicializa al filósofo, configurando su tiempo de última comida y creando el hilo de monitorización de muerte.
void init_philosopher(t_arg *args) {
    args->philo.last_meal_time = current_time();
    pthread_create(&args->monitor_thread, NULL, monitor_death, args);
    pthread_detach(args->monitor_thread);
}

// init_args: Inicializa los argumentos de entrada y los semáforos para la simulación.
void init_args(t_arg *args, int argc, char **argv) {
    memset(args, 0, sizeof(t_arg));
    args->num_philos = atoi(argv[1]);
    args->time_to_die = atol(argv[2]);
    args->time_to_eat = atol(argv[3]);
    args->time_to_sleep = atol(argv[4]);
    if (argc == 6)
        args->num_meals = atoi(argv[5]);
    args->pids = malloc(sizeof(pid_t) * args->num_philos);
    init_semaphores(args);
    init_monitor(args);
}

// start_philosophers: Crea los procesos para cada filósofo y comienza su rutina.
void start_philosophers(t_arg *args) {
    for (int i = 0; i < args->num_philos; i++) {
        args->philo.index = i;
        args->pids[i] = fork();
        if (args->pids[i] == 0) {
            init_philosopher(args);
            philosopher_routine(args);
        }
    }
    sem_wait(args->stop);
}

// cleanup: Libera todos los recursos al finalizar la simulación.
void cleanup(t_arg *args) {
    for (int i = 0; i < args->num_philos; i++) {
        kill(args->pids[i], SIGKILL);
    }
    sem_unlink("forks");
    sem_unlink("write_lock");
    sem_unlink("stop");
    sem_unlink("meals_done");
    free(args->pids);
}
