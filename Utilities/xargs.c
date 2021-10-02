#include "kernel/param.h"
#include "kernel/types.h"
#include "user/user.h"

int readLine(char *line) {
  char buffer[1];
  int i=0;
  while (read(0, buffer, 1) && buffer[0] != '\n') {
    line[i++] = buffer[0];
  }
  line[i] = '\0';
  return i;
}

int main(int argc, char *argv[]) {
  char *tmp="";
  char *args[MAXARG]={""};
  int j=1;
  if (argc < 2) {
  }
  for (int i = 2; i < argc; i++) {
      args[j++] = argv[i];
  }
  while (readLine(tmp)) {
      args[j] = tmp;
      if (fork() == 0 ){
          exec(argv[1], args);
      }
      wait(0);
  }
  exit(0);
}
