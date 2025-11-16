#include "types.h"

struct sysinfo {
  uint64 freemem;   // Số byte bộ nhớ trống
  uint64 nproc;     // Số tiến trình đang hoạt động
};