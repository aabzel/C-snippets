#include "hotel.h"

#include <stdio.h>
#include <stdlib.h>

#include "algorithms.h"

/*
Даны даты заезда и отъезда каждого гостя.
Для каждого гостя дата заезда строго раньше даты отъезда (то есть каждый гость останавливается хотя бы на одну ночь)
Необходимо написать функцию, которая считает максимальное число посетителей, которые одновременно проживали в гостинице.

Ограничение по сложности — строго меньше O(N^2)
*/

static int compara_day(const Event_t *event_a, const Event_t *event_b) {
	return event_a->day - event_b->day;
}

static int find_min_day(Guest_t *guests_array, int num_guests) {
	int cur_min_day = INT_MAX;
	for (int person = 0; person < num_guests; person++) {
		if (guests_array[person].in_day < cur_min_day) {
			cur_min_day = guests_array[person].in_day;
		}
	}
	return cur_min_day;
}

static int find_max_day(Guest_t *guests_array, int num_guests) {
	int cur_out_day = INT_MIN;
	for (int person = 0; person < num_guests; person++) {
		if (cur_out_day < guests_array[person].out_day) {
			cur_out_day = guests_array[person].out_day;
		}
	}
	return cur_out_day;
}

#ifdef DEBUG_HOTEL
static bool debug_guests(Guest_t *guests_array, int num_guests) {
	printf("\n[d] %s()", __FUNCTION__);
	printf("\n");
	bool res = false;
	int min_day = find_min_day(guests_array, num_guests);
	int max_day = find_max_day(guests_array, num_guests);
	for (int day = min_day; day < max_day; day++) {
			printf("%d",day%10);
	}
	printf("\n");

	for (int person = 0; person < num_guests; person++) {
		for (int day = min_day; day < max_day; day++) {
			if ((guests_array[person].in_day <= day)
					&& (day <= guests_array[person].out_day)) {
				printf("_");
			} else {
				printf(".");
			}
		}
		printf("\n");
	}
	return res;
}
#endif

#ifdef DEBUG_HOTEL
static bool debug_events(Event_t *event_array, int num_events) {
	printf("\n[d] %s()", __FUNCTION__);
	bool res = false;
	printf("Event list \n");
	for (int event = 0; event < num_events; event++) {
		printf("(%d %d) ",event_array[event].day,event_array[event].event);
	}
	printf("\n");
	return res;
}
#endif

uint32_t max_guests(Guest_t *guests_array, int num_guests) {
#ifdef DEBUG_HOTEL
	printf("\n[d] %s() ptr %p", __FUNCTION__, guests_array);

	debug_guests(guests_array, num_guests);
#endif
	int max_cnt = 0;
	Event_t *event_array;
	uint32_t size_event_arr = num_guests * 2 * sizeof(Event_t);
	event_array = (Event_t*) malloc(size_event_arr);
	if (event_array) {
		memset(event_array, 0x00, size_event_arr);
		for (int rec = 0; rec < num_guests; rec++) {
			event_array[rec*2].day = guests_array[rec].in_day;
			event_array[rec*2].event = GUEST_IN;

			event_array[rec*2 + 1].day = guests_array[rec].out_day;
			event_array[rec*2 + 1].event = GUEST_OUT;
		}
#ifdef DEBUG_HOTEL
		printf("\n events %d\n",num_guests * 2);
		debug_events(event_array, num_guests * 2);
#endif
		qsort(event_array, num_guests * 2, sizeof(Event_t), compara_day);
		int guest_cnt = 0;
#ifdef DEBUG_HOTEL
		printf("\n sorted events %d\n",num_guests * 2);
		debug_events(event_array, num_guests * 2);
#endif
		for (int event = 0; event < (num_guests * 2); event++) {
#ifdef DEBUG_HOTEL
			if(GUEST_IN==event_array[event].event){
	    		printf("+");
			}else  if(GUEST_OUT==event_array[event].event){
    			printf("-");
			}else{
				printf("[%d]",event_array[event].event);
			}
#endif
			guest_cnt += event_array[event].event;
			max_cnt = max_int(max_cnt, guest_cnt);
		}
		free(event_array);
		event_array = NULL;
	}
	return max_cnt;
}
