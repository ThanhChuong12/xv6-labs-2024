#include "kernel/types.h"
#include "user/user.h"
#include "kernel/fcntl.h"

int
main(int argc, char *argv[])
{
  if (argc < 3) {
    printf("Usage: trace mask command [args...]\n");
    exit(1);
  }
  int mask = atoi(argv[1]);
  if (trace(mask) < 0) {
    printf("trace: failed to set mask\n");
    exit(1);
  }
  exec(argv[2], &argv[2]);
  printf("trace: exec %s failed\n", argv[2]);
  exit(1);
}