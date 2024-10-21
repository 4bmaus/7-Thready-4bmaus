#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "thready.h"

#define PATTERN_PARALLEL 1
#define PATTERN_SEQUENTIAL 2

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Usage: %s <min#> <max#> <pattern#>\n", argv[0]);
        return 1;
    }

    int min_process, max_process, pattern;
    sscanf(argv[1], "%d", &min_process);
    sscanf(argv[2], "%d", &max_process);
    sscanf(argv[3], "%d", &pattern);

    int total_threads = max_process - min_process + 1;
    if (pattern == PATTERN_PARALLEL) {
        thready_parallel(total_threads);
    } else if (pattern == PATTERN_SEQUENTIAL) {
        thready_sequential(total_threads);
    } else {
        printf("Invalid pattern. Use 1 for parallel and 2 for sequential.\n");
        return 1;
    }

    return 0;
}
