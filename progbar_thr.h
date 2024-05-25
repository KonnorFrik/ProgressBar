#ifndef __PROGBAR_THR_H__
#define __PROGBAR_THR_H__

#include <pthread.h>
#include "progbar.h"

/**
 * @brief Create one thread for drawing all given bars
 * @note Can return NULL if any error occured
 * @param[in] arr Not NULL array with progbars
 * @param[in] arr_size size of arr with progbars
 * @return thread ptr to pthread_t
 */
pthread_t* start_drawing_thread(progbar* arr, unsigned int arr_size);

#endif /* __PROGBAR_THR_H__ */
