#include "tasks.h"
#include "pinsInit.h"

void setup() {
  pinsinitTask1_4();
  pinsinitTask2();
  task3();
  task4();
  task5();
  task6();
}

void loop() {
  //task1();
  task2();
}