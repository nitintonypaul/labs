#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int page;
    int last_access;
} pageling;

int simulate_fifo(int *pages, int n, int f);
int simulate_lru(int *pages, int n, int f);
int simulate_optimal(int *pages, int n, int f);

void main() {

    // Obtaining number of pages
    int n;
    printf("Enter the number of pages: ");
    scanf("%d", &n);

    // Obtaining number of frames
    int f;
    printf("Enter the number of frames: ");
    scanf("%d", &f);

    int pages[n];
    for (int i = 0; i < n; i++) {
        printf("Enter page %d: ", i);
        scanf("%d", &pages[i]);
    }

    int fifo_faults = simulate_fifo(pages, n, f);
    int lru_faults = simulate_lru(pages, n, f);
    int optimal_faults = simulate_optimal(pages, n, f);

    printf("-------------------------\n");
    printf("FIFO page faults: %d\n", fifo_faults);
    printf("LRU page faults: %d\n", lru_faults);
    printf("Optimal page faults: %d\n", optimal_faults);
}

int simulate_fifo(int *pages, int n, int f) {
    int *Q = calloc(f, sizeof(int));
    int faults = 0;
    int next = 0;
    for (int i = 0; i < n; i++) {
        int hit = 0;
        for (int j = 0; j < f; j++) {
            // Page hit
            if (Q[j] == pages[i]) {
                hit = 1;
                break;
            }
        }
        if (hit == 0) {
            faults++;
            Q[next] = pages[i];
            next = (next + 1) % f;
        }
    }
    return faults;
}

int simulate_lru(int *pages, int n, int f) {
    pageling Q[f];

    // Filling with dummy pages
    for (int i = 0; i < f; i++) {
        pageling tmp;
        tmp.page = 0;
        tmp.last_access = 0;
        Q[i] = tmp;
    }

    int faults = 0;
    int next = 0;
    for (int i = 0; i < n; i++) {
        int hit = 0;
        for (int j = 0; j < f; j++) {
            // Page hit
            if (Q[j].page == pages[i]) {
                hit = 1;
                Q[j].last_access = i+1;
                break;
            }
        }
        if (hit == 0) {
            // Increment faults and add new page
            faults++;
            pageling temp;
            temp.page = pages[i];
            temp.last_access = i+1;
            Q[next] = temp;
        }
        
        // Find next page to be replaced
        // This step must be done regardless of hit or miss
        int min = n+n;
        for (int i = 0; i < f; i++) {
            if (Q[i].last_access < min) {
                min = Q[i].last_access;
                next = i;
            }
        }
    }

    return faults;
}

int simulate_optimal(int *pages, int n, int f) {
    int *Q = calloc(f, sizeof(int));

    int faults = 0;
    int next = 0;
    for (int i = 0; i < n; i++) {
        int hit = 0;
        for (int j = 0; j < f; j++) {
            // Page hit
            if (Q[j] == pages[i]) {
                hit = 1;
                break;
            }
        }
        if (hit == 0) {
            // Increment faults and add new page
            faults++;
            Q[next] = pages[i];
        }
        
        // Find next optimal page to be replaced
        // This step must be done regardless of hit or miss
        int lowest_future_page_count = n+n;
        for (int j = 0; j < f; j++) {
            int future_page_count = 0;
            for (int k = i+1; k < n; k++) {
                if (pages[k] == Q[j]) future_page_count++;
            }
            if (future_page_count < lowest_future_page_count) {
                lowest_future_page_count = future_page_count;
                next = j;
            }
        }
    }

    return faults;
}