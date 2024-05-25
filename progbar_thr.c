#include "progbar_thr.h"
#include "termcontrol.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct thr_bars_ {
    progbar* arr;
    unsigned int size;
} thr_bars;

static void progbar_draw_thr(progbar* bar) {
    print_bar_(bar);
    printf("\n");
}

void* _printer(void* arg) {
    thr_bars* bars = arg;

    int done = 0;

    while ( !done ) {
        printf(ESC CSI CHIDE);
        done = 1;

        for (unsigned int i = 0; i < bars->size; ++i) {
            progbar_draw_thr(bars->arr + i);

            if ( (bars->arr + i)->current < (bars->arr + i)->max ) {
                done = 0;
            }
        }

        if ( !done ) {
            printf(ESC CSI "%d" CPL, bars->size);
        }

        printf(ESC CSI CSHOW);
    }

    free(bars);
    return arg;
}

pthread_t* start_drawing_thread(progbar* arr, unsigned int arr_size) {
    pthread_t* thread = calloc(1, sizeof(pthread_t));
    thr_bars* bars_info = calloc(1, sizeof(thr_bars));

    if ( thread && bars_info ) {
        bars_info->arr = arr;
        bars_info->size = arr_size;

        if ( pthread_create(thread, 0, _printer, bars_info) ) {
            free(bars_info);
            free(thread);
            thread = NULL;
        }

    } else {
        if ( thread ) {
            free(thread);
            thread = NULL;
        }

        if ( bars_info ) {
            free(bars_info);

        }
    }

    return thread;
}
