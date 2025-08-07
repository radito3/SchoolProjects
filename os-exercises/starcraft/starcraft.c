#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define INITIAL_MINERALS 5000
#define INITIAL_WORKERS 5
#define MARINE_COST 50
#define WORKER_COST 50
#define CMD_COST 400
#define MINERALS_PER_DIGGING 8

typedef struct {
    int minerals;
    pthread_mutex_t minerals_guard;
} CMD;

typedef struct {
    int scv_id;
    int* is_game_running;
    int* map_minerals;
    pthread_mutex_t* map_minerals_guard;
    int* num_cmds;
    CMD** command_centers;
} worker_thread_arg;

typedef struct {
    int* num_cmds;
    int* num_workers;
    int* game_running_flag;
    int* map_minerals;
    pthread_mutex_t* map_minerals_guard;
    CMD** command_centers;
    pthread_t** worker_threads;
} main_cmd_arg;

// is it acceptable for this to view only a snapshot of the total minerals?
int buy_if_available(CMD* command_centers, int num_cmds, int cost) {
    int op_result = 0;
    int cumulative_minerals = 0;
    for (int i = 0; i < num_cmds; i++) {
        // pthread_mutex_lock(&command_centers[i].minerals_guard);
        cumulative_minerals += command_centers[i].minerals;
    }

    if (cumulative_minerals >= cost) {
        // since the command centers' resources are viewed as a "total pool", it doesn't matter which cmd we subtract from
        command_centers[0].minerals -= cost;
        op_result = 1;
    } else {
        printf("Not enough minerals.\n");
    }

    // for (int i = 0; i < num_cmds; i++) {
    //     pthread_mutex_unlock(&command_centers[i].minerals_guard);    
    // }
    return op_result;
}

void* worker_thread(void* arg) {
    worker_thread_arg* arg_val = (worker_thread_arg*) arg;
    // worker lifecycle:
    // - dig 8 minerals (print "SCV N is mining" prior to execution)
    // - transport to a free command center (sleep 2s) (when a cmd center is found and the worker is going there, print "SCV N is transporting minerals")
    //   - if there is no free cmd available, wait 1s and try again
    // - unload minerals (print "SCV N delivered minerals to Command center M" after execution)
    // - loop until the map has no minerals remaining

    while (*arg_val->is_game_running) {
        pthread_mutex_lock(arg_val->map_minerals_guard);
        if (*arg_val->map_minerals < MINERALS_PER_DIGGING) {
            pthread_mutex_unlock(arg_val->map_minerals_guard);
            break;
        }
        printf("SCV %d is mining\n", arg_val->scv_id);
        *arg_val->map_minerals -= MINERALS_PER_DIGGING;
        pthread_mutex_unlock(arg_val->map_minerals_guard);

        int free_cmd_idx = -1;
        while (free_cmd_idx < 0) {
            for (int i = 0; i < *arg_val->num_cmds; i++) {
                if (pthread_mutex_trylock(&(*arg_val->command_centers)[i].minerals_guard) == 0) {
                    free_cmd_idx = i;
                    break;
                }
            }
            if (free_cmd_idx == -1) {
                // sleep(1);
            }
        }

        printf("SCV %d is transporting minerals\n", arg_val->scv_id);
        // sleep(2);
        (*arg_val->command_centers)[free_cmd_idx].minerals += MINERALS_PER_DIGGING;
        printf("SCV %d delivered minerals to Command center %d\n", arg_val->scv_id, free_cmd_idx + 1);
        pthread_mutex_unlock(&(*arg_val->command_centers)[free_cmd_idx].minerals_guard);
    }

    return NULL;
}

void* main_command_center_thread(void* arg) {
    main_cmd_arg* arg_val = (main_cmd_arg*) arg;
    int num_marines = 0;
    int input;

    while ((input = fgetc(stdin)) != EOF) {
        switch ((char) input) {
            case 'm': {
                if (!buy_if_available(*arg_val->command_centers, *arg_val->num_cmds, MARINE_COST)) {
                    break;
                }
                // sleep(1);
                num_marines++;
                printf("You wanna piece of me, boy?\n");
                if ((num_marines + *arg_val->num_workers > 200) || num_marines == 20) {
                    *arg_val->game_running_flag = 0;
                    return NULL;
                }
                break;
            }
            case 's': {
                if (!buy_if_available(*arg_val->command_centers, *arg_val->num_cmds, WORKER_COST)) {
                    break;
                }
                // sleep(1);
                *arg_val->worker_threads = (pthread_t*) realloc(*arg_val->worker_threads, (*arg_val->num_workers + 1) * sizeof(pthread_t));

                worker_thread_arg worker_arg = {
                    .scv_id = *arg_val->num_workers + 1,
                    .command_centers = arg_val->command_centers,
                    .num_cmds = arg_val->num_cmds,
                    .is_game_running = arg_val->game_running_flag,
                    .map_minerals = arg_val->map_minerals,
                    .map_minerals_guard = arg_val->map_minerals_guard
                };
                if (pthread_create(&((*arg_val->worker_threads)[*arg_val->num_workers]), NULL, worker_thread, &worker_arg) != 0) {
                    perror("pthread_create");
                    *arg_val->game_running_flag = 0;
                    return NULL;
                }
                *arg_val->num_workers += 1;
                printf("SCV good to go, sir.\n");
                break;
            }
            case 'c': {
                if (!buy_if_available(*arg_val->command_centers, *arg_val->num_cmds, CMD_COST)) {
                    break;
                }
                // sleep(2);
                *arg_val->command_centers = (CMD*) realloc(*arg_val->command_centers, (*arg_val->num_cmds + 1) * sizeof(CMD));
                (*arg_val->command_centers)[*arg_val->num_cmds].minerals = 0;
                pthread_mutex_init(&(*arg_val->command_centers)[*arg_val->num_cmds].minerals_guard, NULL);
                *arg_val->num_cmds += 1;
                printf("Command center %d created.\n", *arg_val->num_cmds);
                break;
            }
        }
    }

    *arg_val->game_running_flag = 0;

    return NULL;
}

int main(int argc, char* argv[]) {
    int map_minerals = INITIAL_MINERALS;
    int num_workers = INITIAL_WORKERS;
    int num_cmds = 1;
    int is_game_running = 1;
    // other than the "main" command center, the others are just game resources and have no logic to run
    CMD* command_centers = (CMD*) malloc(sizeof(CMD));
    pthread_mutex_t map_minerals_guard;

    pthread_mutex_init(&map_minerals_guard, NULL);

    command_centers[num_cmds - 1].minerals = 0;
    pthread_mutex_init(&command_centers[num_cmds - 1].minerals_guard, NULL);

    pthread_t* worker_threads = (pthread_t*) malloc(sizeof(pthread_t) * INITIAL_WORKERS);
    pthread_t main_cmd_thread;

    main_cmd_arg cmd_arg = {
        .command_centers = &command_centers,
        .num_cmds = &num_cmds,
        .num_workers = &num_workers,
        .game_running_flag = &is_game_running,
        .worker_threads = &worker_threads,
        .map_minerals = &map_minerals,
        .map_minerals_guard = &map_minerals_guard,
    };
    if (pthread_create(&main_cmd_thread, NULL, main_command_center_thread, &cmd_arg) != 0) {
        perror("pthread_create");
        goto end;
    }

    worker_thread_arg worker_args[INITIAL_WORKERS];
    for (int i = 0; i < num_workers; i++) {
        worker_args[i].scv_id = i + 1;
        worker_args[i].command_centers = &command_centers;
        worker_args[i].num_cmds = &num_cmds;
        worker_args[i].is_game_running = &is_game_running;
        worker_args[i].map_minerals = &map_minerals;
        worker_args[i].map_minerals_guard = &map_minerals_guard;
        if (pthread_create(&worker_threads[i], NULL, worker_thread, &worker_args[i]) != 0) {
            perror("pthread_create");
            // goto end;
        }
    }

    // each subsequent cmd after the first can only be used for unloading minerals, not to train soldiers or workers

    if (pthread_join(main_cmd_thread, NULL) != 0) {
        perror("pthread_join");
        // goto end;
    }

    for (int i = 0; i < num_workers; i++) {
        if (pthread_join(worker_threads[i], NULL) != 0) {
            perror("pthread_join");
            // goto end;
        }
    }

    // this is after the purchases
    int total_collected_minerals = 0;
    for (int i = 0; i < num_cmds; i++) {
        total_collected_minerals += command_centers[i].minerals;
    }
    printf("Initial minerals %d, remaining minerals %d, Total collected %d\n", INITIAL_MINERALS, map_minerals, total_collected_minerals);

end:
    pthread_mutex_destroy(&map_minerals_guard);
    for (int i = 0; i < num_cmds; i++) {
        pthread_mutex_destroy(&command_centers[i].minerals_guard);
    }
    free(worker_threads);
    free(command_centers);
    return 0;
}
