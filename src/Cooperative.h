#ifndef Cooperative_H
#define Cooperative_H

// Task Control Block 2
typedef struct {
  int state;
  char name;
} Tcb2;

// Task Control Block 1
typedef struct {
  int state;
  char name;
  Tcb2 *tcb2;
} Tcb1;

int task2(Tcb2 *tb, int v1, float v2);
double task1(Tcb1 *tb);

Tcb1 *createTask1Tcb(char name);
Tcb2 *createTask2Tcb(char name);

#endif // Cooperative_H
