#include <stdint.h>   // uint64_t
#include <stdbool.h>  // bool

#ifndef PERSON_H
#define PERSON_H

#define PERSON_NAME_MAX_LENGTH 255

typedef struct person {
  char * name;          // name
  uint64_t age;         // age in ticks
  uint64_t lifespan;    // life span in ticks
  bool dead;
} person_t;

person_t * person_create(void);
void person_destroy(person_t * person);
void person_tick(person_t * person);

#endif