#define _DEFAULT_SOURCE
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "progbar.h"
#include "progbar_thr.h"

void ex1() {
    progbar bar;
    progbar_init(&bar);
    bar.info = "TestBar";

    for (; bar.current <= bar.max && !progbar_update(&bar, 1);) {
        progbar_draw(&bar);
        usleep(15000);
    }
}

void ex2() {
    progbar bar;
    progbar_init(&bar);
    bar.info = "This is";
    bar.empty = '.';
    bar.fill = '#';
    bar.fmt = "%i cur:%c. %i max:%m. %i bar:%b. %i info:'%i'";

    for (; bar.current <= bar.max && !progbar_update(&bar, 1);) {
        progbar_draw(&bar);
        usleep(35000);
    }
}

void ex3() {
    int count = 2;
    progbar* bars = calloc(count, sizeof(progbar));
    for (int i = 0; i < count; ++i) {
        progbar_init(bars + i);
        (bars + i)->info = "bar";
        (bars + i)->max = 200;
    }

    // bar.empty = '.';
    // bar.fill = '#';
    // bar.fmt = "%i cur:%c. %i max:%m. %i bar:%b. %i info:'%i'";

    pthread_t* printer = start_drawing_thread(bars, count);

    if ( !printer ) {
        printf("Can't create printer\n");
        exit(1);
    }

    int done = 0;

    while ( !done ) {
        done = 1;

        for (int i = 0; i < count; ++i) {
            if ( progbar_update(bars + i, 1) == 0 ) {
                done = 0;
            }
        }

        usleep(25000);
    }

}

int main () {
    // ex1();
    // ex2();
    ex3();
    return 0;
}
