#include <stdio.h>
#include "Cooperative.h"
#include "Tasker.h"

int task2(int v1, float v2) {
  static TaskBlock taskBlock = {.state = 0};
  TaskBlock *tb = &taskBlock;

  startTask(tb);

  printf("\ttask2: 1 (%d) | yield\n", v1);
  yield(tb);

  printf("\ttask2: 2 (%f) | yield\n", v2);
  yield(tb);

  if(v1 < 500) {
    printf("\ttask2: 3 | return 111\n");
    returnThis(111, tb);
  } else {
    printf("\ttask2: 3 | return 999\n");
    returnThis(999, tb);
  }

  endTask(tb);
}


double task1() {
  static TaskBlock taskBlock = {.state = 0};
  TaskBlock *tb = &taskBlock;
  int result;

  startTask(tb);

  printf("task1: 1 | yield\n");
  yield(tb);

  // The following will wait till task2() returns. The result will
  // be stored in 'result'.
  await(result, task2(34, 67.8976), tb);

  printf("task1: 2 (result from task2 = %d) | yield\n", result);
  yield(tb);

  // The following will wait till task2() returns. The result will
  // be stored in 'result'.
  await(result, task2(98765, 0.123456), tb);

  printf("task1: 3 (result from task2 = %d) | yield\n", result);
  yield(tb);

  printf("task1: 4 | return 789.12345\n");
  returnThis(789.12345, tb);

  endTask(tb);
}