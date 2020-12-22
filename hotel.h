#ifndef HOTEL_H
#define HOTEL_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#define DEBUG_HOTEL

typedef enum {
	GUEST_IN = 1,
	GUEST_OUT = -1
}eEvent_t;

typedef struct xGuest_t {
  int in_day;
  int out_day;
} Guest_t;

typedef struct xEvent_t {
  int day;
  eEvent_t event;
} Event_t;

uint32_t max_guests(Guest_t *guests_array, int size);


#ifdef __cplusplus
}
#endif

#endif /*HOTEL_H*/
