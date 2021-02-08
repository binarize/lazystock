#include <stdint.h>   // uint64_t
#include <stdbool.h>  // bool

#ifndef RESOURCE_H
#define RESOURCE_H

#define RESOURCE_NAME_MAX_LENGTH 255

// Our faux constants for the hardcoded resources.
extern uint64_t resource_id_labour;
extern uint64_t resource_id_happiness;
extern uint64_t resource_id_health;

typedef struct resource {
  char * name;          // name
  uint64_t age;         // age in ticks
  uint64_t lifespan;    // life span in ticks
  bool tradable;        // is it tradable.
} resource_t;


resource_t * resource_create(void);
void resource_destroy(resource_t * resource);
resource_t ** resource_add_essentials(resource_t ** resources, uint64_t * resources_len);

#endif