#include <stdlib.h>  // rand(), srand()
#include <time.h>    // time()
#include <stdint.h>
#include <stdio.h>


#include <world.h>

/**
 * Entry point
 */
int main(int argc, char *argv[])
{

  (void) argc;
  (void) argv;

  // Random seed,
  srand(time(0));

  world = world_create();
  printf("Hello world\n"); // the one time this is actually applicable!

  // Seed the world
  world_seed(world, 0);

  // Run the simulation for a year.
  for(uint64_t i = 0; i < WORLD_TICKS_PER_YEAR; i++) {
    world_tick(world);
  }

  world_destroy(world);
  printf("Goodbye cruel world\n");

  // Tell OS everything ran fine.
  return 0;

}
