// File: user/sysinfotest.c
#include "kernel/types.h"
#include "kernel/riscv.h"
#include "kernel/sysinfo.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
    struct sysinfo info;

    printf("sysinfotest: starting\n");

    if (sysinfo(&info) < 0) {
        printf("sysinfotest: sysinfo failed\n");
        exit(1);
    }

    // Kiểm tra xem các giá trị có hợp lý không
    if (info.freemem < 0 || info.nproc < 1) {
        printf("sysinfotest: invalid values\n");
        exit(1);
    }

    printf("sysinfotest: OK\n");
    exit(0);
}