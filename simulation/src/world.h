#include <stdint.h> // uint64_t
#include <stdlib.h> // malloc()

#include "person.h"

#ifndef WORLD_H
#define WORLD_H






#define WORLD_DATE_MINUTES_PER_HOUR 60
#define WORLD_DATE_HOURS_PER_DAY 24
#define WORLD_DATE_DAYS_PER_MONTH 30
#define WORLD_DATE_MONTHS_PER_YEAR 12

#define WORLD_DATE_SECONDS_PER_MINUTE 60
#define WORLD_DATE_SECONDS_PER_HOUR (WORLD_DATE_SECONDS_PER_MINUTE * WORLD_DATE_MINUTES_PER_HOUR)
#define WORLD_DATE_SECONDS_PER_DAY (WORLD_DATE_SECONDS_PER_HOUR * WORLD_DATE_HOURS_PER_DAY)
#define WORLD_DATE_SECONDS_PER_MONTH (WORLD_DATE_SECONDS_PER_DAY * WORLD_DATE_DAYS_PER_MONTH)
#define WORLD_DATE_SECONDS_PER_YEAR (WORLD_DATE_SECONDS_PER_MONTH * WORLD_DATE_MONTHS_PER_YEAR)

#define WORLD_SECONDS_PER_TICK (60*60*24)
#define WORLD_TICKS_PER_YEAR (WORLD_DATE_SECONDS_PER_YEAR / WORLD_SECONDS_PER_TICK)


// our custom date structure.
typedef struct date {
  uint64_t second;
  uint64_t minute;
  uint64_t hour;
  uint64_t day;
  uint64_t month;
  uint64_t year;
} date_t;

typedef struct world {
  uint64_t tick;          // how many ticks in total
  date_t date;            // current date (based on the tick)
  person_t ** people;
  uint64_t people_len;
} world_t;

extern world_t * world;

world_t * world_create(void);
void world_destroy(world_t * world);
void world_seed(world_t * world, uint64_t seed);
void world_tick(world_t * world);
person_t * world_spawn_person(world_t * world);
void world_date_from_tick(uint64_t tick, date_t * date);

#endif