#include "kernel/types.h"
#include "user/user.h"

void GenerateNatural(int *p1) {
  close(p1[0]);
  for (int j = 2; j <= 35; j++) {
    if (write(p1[1], &j, sizeof(int)) < 0) {
      exit(1);
    }
  }
  close(p1[1]);
}

void PrimeFilter(int *p1) {
  close(p1[1]);
  int prime = 0;
  int buffer[1];
  switch (read(p1[0], &buffer, sizeof(int))) {
    case 0:
      exit(0);
      break;
    case sizeof(int):
      printf("prime %d\n", buffer[0]);
      prime = buffer[0];
      break;
    default:
      exit(1);
  }

  int p2[2];
  if (pipe(p2) < 0) {
    printf("pipe err\n");
    exit(1);
  }

  if (fork() == 0) {
    PrimeFilter(p2);
  }

  close(p2[0]);
  while (read(p1[0], &buffer, sizeof(int)) > 0) {
    if (buffer[0] % prime == 0) {
      continue;
    }
    if (write(p2[1], buffer, sizeof(int)) <= 0) {
      exit(1);
    }
  }
  close(p2[1]);
  close(p1[0]);
  wait(0);
  exit(0);
}

int main(int argc, char *argv[]) {
  int p1[2];
  if (pipe(p1) < 0) {
    exit(1);
  }

  if (fork() == 0) {
    PrimeFilter(p1);
  }

  GenerateNatural(p1);
  wait(0);
  exit(0);
}