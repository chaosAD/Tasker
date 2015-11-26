#include <stdio.h>
#include "unity.h"
#include "Cooperative.h"
#include "Tasker.h"

#define hasNoResult   isYielding
#define hasResult     (!hasNoResult)

void setUp(void) {}

void tearDown(void) {}

void test_tasker_yield() {
  double resultA, resultB;
  int allDone, doneA = 0, doneB = 0;
  Tcb1 tcbA = {.state = 0, .name = 'A'};
  Tcb1 tcbB = {.state = 0, .name = 'B'};

  // Main loop that executes all base tasks
  do {
    if(!doneA) {
      resultA = task1(&tcbA);
      doneA = hasResult;
    }
    if(!doneB) {
      resultB = task1(&tcbB);
      doneB = hasResult;
    }
    allDone = doneA & doneB;
  } while(!allDone);

  printf("A: Got %f\n", resultA);
  printf("B: Got %f\n", resultB);
}
