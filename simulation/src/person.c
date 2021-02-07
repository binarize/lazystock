#include <stdio.h>  // printf()

#include "person.h"
#include "world.h"

person_t * person_create(void)
{

  // Birth our person.
  person_t * person = malloc(sizeof(person_t));

  // Reset a few things
  person->age = 0;
  person->birthday_tick = (rand() % WORLD_TICKS_PER_YEAR);
  person->name = malloc(sizeof(char) * PERSON_NAME_MAX_LENGTH);

  char * firstname = "Scoobert";
  char * lastname = "Doo";
  snprintf(person->name, PERSON_NAME_MAX_LENGTH, "%s %s", firstname, lastname);

  return person;

}

void person_destroy(person_t * person)
{


  free(person->name);
  free(person);

}

void person_tick(person_t * person) 
{

  if (person->dead) {
    printf("BUG - should not have been able to reach this\n");
    abort();
  }

  // Check for birthday
  if ((world->tick % person->birthday_tick) == 0) {
    person->age++;
    // Prevent immortality!
    if (person->age == PERSON_MAX_AGE) {
      person->dead = true;
      return;
      //printf("\tPerson: %s died of old age at %i years old\n", person->name, person->age);
    }
  }

  // Random chance of death, weighted towards older age.
  if (!person->dead) {
    // @TODO - the below is messy and temporary, replace it with a nicer probability function.
    // Exponential chance as they appoach max age..
    bool chance_of_death = ((rand() % PERSON_MAX_AGE) <= person->age) && ((rand() % PERSON_MAX_AGE) <= person->age) && ((rand() % PERSON_MAX_AGE) <= person->age) && ((rand() % PERSON_MAX_AGE) <= person->age);
    if (chance_of_death) {
      // one having a one in per year chance of just randomly dropping dead..
      person->dead = (rand() % (int) WORLD_TICKS_PER_YEAR) == 0;
      //printf("\tPerson: %s died suddenly at %i years old\n", person->name, person->age);

      if (person->dead) {
        return;
      }

    }
  }

  // Good, they are still kicking..

  // @TODO


}

