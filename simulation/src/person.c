#include <stdio.h>  // printf()

#include "person.h"
#include "world.h"

person_t * person_create(void)
{

  // Birth our person.
  person_t * person = malloc(sizeof(person_t));

  person->age = 0;
  person->lifespan = 0;
  person->name = malloc(sizeof(char) * PERSON_NAME_MAX_LENGTH);


  return person;

}

void person_destroy(person_t * person)
{

  free(person->name);
  free(person);

}

void person_tick(person_t * person)
{

  // Increment their age.
  person->age++;

  // Check for death conditions
  if (person->age >= person->lifespan) {
    person->dead = true;
    //printf("\tPerson: %s died of old age at %llu years old\n", person->name, person->age / WORLD_TICKS_PER_YEAR);
    return;
  }


  // Good, they are still kicking..

  // @TODO


}

