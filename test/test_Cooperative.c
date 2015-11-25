#include <stdio.h>
#include "unity.h"
#include "Cooperative.h"
#include "Tasker.h"

#define hasNoResult   isYielding

void setUp(void) {}

void tearDown(void) {}

void test_tasker_yield() {
  double result;

  // Main loop that executes all base tasks
  do {
    result = task1();
  } while(hasNoResult);

  printf("Got %f\n", result);
}
