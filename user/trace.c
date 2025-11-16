#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        fprintf(2, "Usage: trace <mask> <command> [arguments...]\n");
        fprintf(2, "Example: trace 32 grep hello README\n");
        exit(0);
    }

    int mask = atoi(argv[1]);

    // Gọi syscall trace để bật mask
    if (trace(mask) < 0)
    {
        fprintf(2, "trace: syscall failed\n");
        exit(0);
    }

    // exec chương trình cần trace
    exec(argv[2], &argv[2]);

    fprintf(2, "trace: exec %s failed\n", argv[2]);
    exit(0);
}