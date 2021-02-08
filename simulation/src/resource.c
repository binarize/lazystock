#include <stdio.h>  // printf()
#include <stdlib.h> // malloc()

#include "resource.h"

uint64_t resource_id_labour = 0;
uint64_t resource_id_happiness = 0;
uint64_t resource_id_health = 0;


resource_t ** resource_add_essentials(resource_t ** resources, uint64_t * resources_len)
{

  // Add space for 3 more.
  resources = realloc(resources, sizeof(resource_t*) * ((*resources_len) + 3)); // 0 + 3

  // Add the new resources in and update the globals.
  resource_id_labour = *resources_len;  // 0
  resources[resource_id_labour] = resource_create();
  (*resources_len)++; // 1

  resource_id_happiness = *resources_len;  // 1
  resources[resource_id_happiness] = resource_create();
  (*resources_len)++; // 2

  resource_id_health = *resources_len; // 2
  resources[resource_id_health] = resource_create();
  (*resources_len)++; // 3

  return resources;

}

resource_t * resource_create(void)
{
  resource_t * resource = malloc(sizeof(resource_t));
  resource->age = 0;
  resource->lifespan = 0;
  resource->name = malloc(sizeof(char) * RESOURCE_NAME_MAX_LENGTH);
  return resource;
}

void resource_destroy(resource_t * resource)
{
  free(resource->name);
  free(resource);
}
