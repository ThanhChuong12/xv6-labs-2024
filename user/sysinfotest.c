#include "../kernel/types.h"
#include "../kernel/stat.h"
#include "../user/user.h"
#include "../kernel/sysinfo.h"

void test_call() {
  struct sysinfo si;
  if (sysinfo(&si) < 0) {
    printf("sysinfotest: sysinfo failed\n");
    exit(1);
  }
}

void test_mem() {
  struct sysinfo si;
  sysinfo(&si);
  if (si.freemem == 0) {
    printf("sysinfotest: freemem is zero\n");
    exit(1);
  }
}

void test_proc() {
  struct sysinfo si;
  sysinfo(&si);
  if (si.nproc == 0) {
    printf("sysinfotest: nproc is zero\n");
    exit(1);
  }
}

int main() {
  test_call();
  test_mem();
  test_proc();
  
  printf("sysinfotest: OK\n");
  exit(0);
}
