#ifndef __PROGBAR_H__
#define __PROGBAR_H__

/**
 * Format specification
 * any format token must be leading with '%'
 * tokens:
 * i - print progbar.info if not NULL
 * b - print bar 
 * c - print progbar.current as int
 * m - print progbar.max as int
 * % - print '%'
 */

typedef struct progbar {
    unsigned int max; ///< maximum value for progress counting. Default: 100
    unsigned int current; ///< current progress. Start from 0
    unsigned int char_len; ///< how long draw the bar. Default: 30

    char* info; ///< 0-terminating string with info about this bar. Default: NULL
    char* fmt;  ///< 0-terminating string with format for draw bar. Default: ...
    char empty; ///< draw this as empty
    char fill;  ///< draw this as filled
    char head;  ///< draw this as head
} progbar;

/**
 * @brief Init bar with default values
 * @warning if bar is NULL -> segfault
 * @param[in, out] bar progbar valid object
 * @return void
 */
void progbar_init(progbar* bar);

/**
 * @brief Draw given bar in stdout
 * @warning if bar is NULL -> segfault
 * @param[in] bar progbar valid object
 * @return void
 */
void progbar_draw(progbar* bar);

/**
 * @brief Update progress in bar object on given value
 * @warning if bar is NULL -> segfault
 * @param[in, out] bar progbar valid object
 * @param[in]      value value for add to progress
 * @return is_full Is progress reach max, 0-No, 1-Yes
 */
int progbar_update(progbar* bar, unsigned int value);


/**
 * @brief Print only formatted bar
 * @warning Don't use directly
 * @param[in] bar Not NULL progbar object
 * @return void
 */
void print_bar_(progbar* bar);

#endif /* __PROGBAR_H__ */
