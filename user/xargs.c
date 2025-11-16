#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/param.h"

#define MAX_LINE_LEN 512

int main(int argc, char *argv[]) {
    char *command_argv[MAXARG]; 
    char line_buf[MAX_LINE_LEN];  // buffer để đọc 1 dòng từ stdin
    char *p;
    int i;

    // check có lệnh nào được truyền hông
    if (argc < 2) {
        fprintf(2, "Usage: xargs <command> [args...]\n");
        exit(1);
    }

    // Copy lệnh và đối số ban đầu từ argv của xargs
    // sang command_argv. Bỏ qua argv[0] ("xargs").
    for (i = 1; i < argc; i++) {
        command_argv[i - 1] = argv[i];
    }
    
    // đọc từng dòng từ stdin
    while (1) {
        p = line_buf; // reset con trỏ về đầu buffer mỗi dòng mới

        // Đọc cho đến khi gặp '\n' hoặc hết file
        while (read(0, p, 1) > 0) {
            if (*p == '\n') {
                break; // end
            }
            p++;
            if (p >= line_buf + MAX_LINE_LEN) {
                fprintf(2, "xargs: input line too long\n");
                exit(1);
            }
        }
        
        // Nếu đọc hết input
        if (p == line_buf) {
            break; 
        }

        *p = 0; 

        // fork 1 tiến trình mới để chạy lệnh
        if (fork() == 0) {
            // thêm dòng vừa đọc được làm đối số cuối cùng
            command_argv[argc - 1] = line_buf;
            // đặt phần tử tiếp theo là NULL để kết thúc mảng argv
            command_argv[argc] = 0;

            // chạy lệnh
            exec(command_argv[0], command_argv);

            // nếu exec() trả về, --> thất bại
            fprintf(2, "xargs: exec %s failed\n", command_argv[0]);
            exit(1);
        } else {
            // tiến trình cha đợi tiến trình con kết thúc
            wait(0);
        }
    }

    exit(0);
}