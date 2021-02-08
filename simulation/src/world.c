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
  world->resources = NULL;
  world->resources_len = 0;

  return world;
}


void world_destroy(world_t * world)
{

  for(uint64_t i = 0; i < world->people_len; i++)
  {
    person_destroy(world->people[i]);
  }

  for(uint64_t i = 0; i < world->resources_len; i++)
  {
    resource_destroy(world->resources[i]);
  }

  free(world);

}


void world_seed(world_t * world, uint64_t seed)
{

  // Seed people
  for(uint64_t i = 0; i < 1000; i++)
  {
    world_spawn_person(world);
  }

  // Seed our resources
  world->resources = resource_add_essentials(world->resources, &world->resources_len);
  // Some randomly generated ones
  for (uint64_t i = 0; i < 100; i++) {
    world_spawn_resource(world);
  }


  // Create our hard-coded items

  // Happiness
  // Health
  // Labour



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

  // Create them and add them to the world.
  person_t * person = person_create();
  world->people_len++;
  world->people = realloc(world->people, sizeof(person_t*) * world->people_len);
  world->people[world->people_len - 1] = person;


  // Start them at a random age.
  person->age = rand() % PERSON_MAX_LIFESPAN;

  // Calcualte their life span as a random number
  // based on the amount of life they have remaining
  // but weight it more towards the higher end,
  int ticks_remaining = PERSON_MAX_LIFESPAN - person->age;
  person->lifespan = (rand() % ticks_remaining * 2) + 1;
  if (person->lifespan > PERSON_MAX_LIFESPAN) {
    person->lifespan = PERSON_MAX_LIFESPAN;
  }

  // Generate a random name
  char * firstname = "Scoobert";
  char * lastname = "Doo";
  snprintf(person->name, PERSON_NAME_MAX_LENGTH, "%s %s", firstname, lastname);


  return person;

}


resource_t * world_spawn_resource(world_t * world) {

  resource_t * resource = resource_create();

  // Add the person to teh world.
  world->resources_len++;
  world->resources = realloc(world->resources, sizeof(resource_t*) * world->resources_len);
  world->resources[world->resources_len - 1] = resource;

  return resource;

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