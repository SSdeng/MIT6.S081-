#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char *argv[]) {
  char buffer[1];
  int p1[2];
  int p2[2];
  if (pipe(p1) < 0) {
    printf("pipe1 failed\n");
    exit(1);
  }
  if (pipe(p2) < 0) {
    printf("pipe2 failed\n");
    exit(1);
  }

  if (fork() == 0) {
    if (read(p1[0], &buffer, 1) < 0) {
      exit(1);
    }
    printf("%d: received ping\n", getpid());
    if (write(p2[1], "w", 1) < 0) {
      exit(1);
    }
    exit(0);
  }
  
  if (write(p1[1], "w", 1) < 0) {
    exit(1);
  }
  if (read(p2[0], &buffer, 1) < 0) {
    exit(1);
  }
  printf("%d: received pong\n", getpid());
  wait(0);
  exit(0);
}

