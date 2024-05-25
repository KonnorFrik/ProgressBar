#include <stdio.h>
#include "termcontrol.h"
#include "progbar.h"

enum fmt_token {
    INFO = 'i',
    BAR = 'b',
    CUR_NUM = 'c',
    MAX_NUM = 'm',
    PERCENT = '%',
};

#define BAR_MAX 100
#define BAR_CHARLEN 30
#define BAR_FMT "%i%b %c/%m"
#define BAR_EMPTY ' '
#define BAR_FILL '-'
#define BAR_HEAD '>'

#define BAR_TOKEN_SYMB '%'

void progbar_init(progbar* bar) {
    bar->max = BAR_MAX;
    bar->current = 0;
    bar->char_len = 30;
    bar->info = 0;
    bar->fmt = BAR_FMT;
    bar->empty = BAR_EMPTY;
    bar->fill = BAR_FILL;
    bar->head = BAR_HEAD;
}

void print_bar_(progbar* bar) {
    unsigned int cur_prog = ( bar->current * 100 / bar->max ) * bar->char_len / 100;
    unsigned int ind = 0;

    while ( bar->fmt[ind] ) {
        if ( bar->fmt[ind] == BAR_TOKEN_SYMB ) {
            ind++;

            switch ( bar->fmt[ind] ) {
                case INFO:
                    if ( bar->info ) {
                        printf("%s", bar->info);
                    }
                    break;
                case BAR:
                    printf("[");
                    for (unsigned int i = 0; i < cur_prog; ++i) {
                        printf("%c", bar->fill);
                    }

                    if ( bar->current < bar->max ) {
                        printf(BS "%c", bar->head);
                    }

                    for (unsigned int i = 0; i < (bar->char_len - cur_prog); ++i) {
                        printf("%c", bar->empty);
                    }
                    printf("]");
                    break;
                case CUR_NUM:
                    printf("%d", bar->current);
                    break;
                case MAX_NUM:
                    printf("%d", bar->max);
                    break;
                case PERCENT:
                    printf("%%");
                    break;
            }
        } else {
            printf("%c", bar->fmt[ind]);
        }

        ind++;
    }
}

void progbar_draw(progbar* bar) {
    printf(ESC CSI CHIDE);

    // printf(CR);
    printf(ESC CSI "%d" CPL, 1);

    print_bar_(bar);

    // fflush(stdout);
    printf("\n");
    printf(ESC CSI CSHOW);
}

int progbar_update(progbar* bar, unsigned int value) {
    int result = 0;
    bar->current += value;

    if ( bar->current > bar->max ) {
        bar->current = bar->max;
        result = 1;
    }

    return result;
}
