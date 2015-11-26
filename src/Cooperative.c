#include <stdio.h>
#include <malloc.h>
#include "Cooperative.h"
#include "Tasker.h"

Tcb1 *createTask1Tcb(char name) {
  Tcb1 *tcb = malloc(sizeof(Tcb1));
  tcb->state = 0;
  tcb->name = name;
  return tcb;
}

Tcb2 *createTask2Tcb(char name) {
  Tcb2 *tcb = malloc(sizeof(Tcb2));
  tcb->state = 0;
  tcb->name = name;
  return tcb;
}

int task2(Tcb2 *tcb, int v1, float v2) {
  startTask(tcb);

  printf("\ttask%c2: 1 (%d) | yield\n", tcb->name, v1);
  yield(tcb);

  printf("\ttask%c2: 2 (%f) | yield\n", tcb->name, v2);
  yield(tcb);

  if(v1 < 500) {
    printf("\ttask%c2: 3 | return 111\n");
    returnThis(111, tcb);
  } else {
    printf("\ttask%c2: 3 | return 999\n");
    returnThis(999, tcb);
  }

  endTask(tcb);
}


double task1(Tcb1 *tcb) {
  int result;

  startTask(tcb);

  printf("task%c1: 1 | yield\n", tcb->name);
  yield(tcb);

  // The following will wait till task2() returns. The result will
  // be stored in 'result'.
  tcb->tcb2 = createTask2Tcb(tcb->name);
  await(result, task2(tcb->tcb2, 34, 67.8976), tcb);

  printf("task%c1: 2 (result from task2 = %d) | yield\n", tcb->name, tcb->name, result);
  yield(tcb);

  // The following will wait till task2() returns. The result will
  // be stored in 'result'.
  resetTask(tcb->tcb2);
  await(result, task2(tcb->tcb2, 98765, 0.123456), tcb);
  free(tcb->tcb2);

  printf("task%c1: 3 (result from task%c2 = %d) | yield\n", tcb->name, tcb->name, result);
  yield(tcb);

  printf("task%c1: 4 | return 789.12345\n", tcb->name);
  returnThis(789.12345, tcb);

  endTask(tcb);
}