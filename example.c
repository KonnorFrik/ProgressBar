#define _DEFAULT_SOURCE
#include <unistd.h>
#include "progbar.h"

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

int main () {
    // ex1();
    ex2();
    return 0;
}
