#include <stdio.h>  // printf()
#include <math.h>   // floor()

#include "world.h"


world_t * world;


world_t * world_create(void) 
{
  // Create the world.
  world_t * world = malloc(sizeof(world_t));

  // Reset some things
  world->tick = 0;
  world_date_from_tick(world->tick, &world->date);
  world->people = NULL;
  world->people_len = 0;

  return world;
}


void world_destroy(world_t * world) 
{

  if (world->people_len > 0) 
  {
    for(uint64_t i = 0; i < world->people_len; i++) 
    {
      person_destroy(world->people[i]);
    }
    free(world);
  }

}


void world_seed(world_t * world, uint64_t seed)
{
  
  // Birth a few people to begin with.
  for(uint64_t i = 0; i < 1000; i++)
  {
    person_t * newbie = world_spawn_person(world);
    newbie->age = rand() % (PERSON_MAX_AGE / 2); // between 0 and middle age.
  }

}

void world_tick(world_t * world) 
{

  // Move things along..
  world->tick++;
  world_date_from_tick(world->tick, &world->date);

  printf("Tick: %llu Population: %llu Date: [%04llu-%02llu-%02llu %02llu:%02llu:%02llu]\n", world->tick, world->people_len, world->date.year, world->date.month, world->date.day, world->date.hour, world->date.minute, world->date.second);

  // Update all the people.
  uint64_t living_people_count = 0;
  for(uint64_t i = 0; i < world->people_len; i++) 
  {
    person_t * person = world->people[i];
    person_tick(person);
    if (!person->dead) {
      living_people_count++;
    }
  }

  // Prune dead people from our world.
  person_t ** living_people = malloc(sizeof(person_t*) * living_people_count);
  uint64_t people_count = 0;
  for(uint64_t i = 0; i < world->people_len; i++) 
  {
    person_t * person = world->people[i];
    if (!person->dead) {
      living_people[people_count] = person;
      people_count++;
    } else {
      person_destroy(person);
    }
  }
  free(world->people);
  world->people = living_people;
  world->people_len = living_people_count;


}



person_t * world_spawn_person(world_t * world) 
{

  person_t * person = person_create();


  // Add the person to teh world.
  world->people_len++;
  world->people = realloc(world->people, sizeof(person_t*) * world->people_len);
  world->people[world->people_len - 1] = person;

  // Return it to whatever spawned the person,
  return person;

}


void world_date_from_tick(uint64_t tick, date_t * date) 
{

  // Convert it from ticks into seconds..
  uint64_t seconds = tick * WORLD_SECONDS_PER_TICK;

  // Work out the date based on seconds.
  date->year = floor(seconds / WORLD_DATE_SECONDS_PER_YEAR);
  seconds -= (date->year * WORLD_DATE_SECONDS_PER_YEAR);
  date->year +=1970; // Start from 1970.

  date->month = floor(seconds / WORLD_DATE_SECONDS_PER_MONTH);
  seconds -= (date->month * WORLD_DATE_SECONDS_PER_MONTH);
  date->month +=1; // Months start from 1 instead of 0

  date->day = floor(seconds / WORLD_DATE_SECONDS_PER_DAY);
  seconds -= (date->day * WORLD_DATE_SECONDS_PER_DAY);
  date->day +=1; // Days go from 1 instead of 0

  date->hour = floor(seconds / WORLD_DATE_SECONDS_PER_HOUR);
  seconds -= (date->hour * WORLD_DATE_SECONDS_PER_HOUR);

  date->minute = floor(seconds / WORLD_DATE_SECONDS_PER_MINUTE);
  seconds -= (date->minute * WORLD_DATE_SECONDS_PER_MINUTE);

  date->second = seconds;

}