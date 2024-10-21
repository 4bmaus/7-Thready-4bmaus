#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include "thready.h"

// Function to be executed by each thread
void* thread_work(void* arg) {
    int thread_num = *(int*)arg;  // Thread number passed as argument
    printf("Thread %d (TID %lu) beginning\n", thread_num, pthread_self());
    sleep(1 + (rand() % 8));  // Simulate work with random sleep
    printf("Thread %d (TID %lu) exiting\n", thread_num, pthread_self());
    return NULL;
}

void thready_parallel(int num_threads) {
    srand(time(NULL));
    pthread_t threads[num_threads];
    int thread_nums[num_threads];

    for (int i = 0; i < num_threads; ++i) {
        thread_nums[i] = i + 1;
        if (pthread_create(&threads[i], NULL, thread_work, &thread_nums[i]) != 0) {
            perror("Failed to create thread");
            exit(EXIT_FAILURE);
        }
    }

    // Wait for all threads to finish
    for (int i = 0; i < num_threads; ++i) {
        pthread_join(threads[i], NULL);
    }
}

void thready_sequential(int num_threads) {
    srand(time(NULL));
    pthread_t thread;
    int thread_num;

    for (int i = 0; i < num_threads; ++i) {
        thread_num = i + 1;
        if (pthread_create(&thread, NULL, thread_work, &thread_num) != 0) {
            perror("Failed to create thread");
            exit(EXIT_FAILURE);
        }
        pthread_join(thread, NULL);  // Wait for the current thread to finish before starting the next
    }
}
