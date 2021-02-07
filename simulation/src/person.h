#include <stdint.h>		// uint64_t
#include <stdbool.h> 	// bool

#ifndef PERSON_H
#define PERSON_H

#define PERSON_MAX_AGE 100
#define PERSON_NAME_MAX_LENGTH 255

typedef struct person {
	char * name;			// there name
	uint8_t age;
	uint8_t birthday_tick;
	bool dead;
} person_t;

person_t * person_create(void);
void person_destroy(person_t * person);
void person_tick(person_t * person);

#endif