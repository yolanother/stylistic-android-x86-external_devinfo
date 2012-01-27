#include <cmath>
#include <cerrno>
#include <cstring>
#include <sys/stat.h>
#include <poll.h>
#include <fcntl.h>
#include <dirent.h>
#include <cutils/log.h>
#include <linux/input.h>
#include <linux/uinput.h>
#include <hardware/sensors.h>
#include <stdio.h>

#define LOG_TAG "Device Info"

int main(int count, char**args) {    
    char name[PATH_MAX];
    int fd = 0;
    int i;

    for(i = 1; i < count; i++) {
        fd = open(args[i], O_RDWR);
        if (fd < 0) {
            LOGE("could not open %s, %s", name, strerror(errno));
        } else {
            name[sizeof(name) - 1] = '\0';
            if (ioctl(fd, EVIOCGNAME(sizeof(name) - 1), &name) < 1) {
                LOGE("could not get device name for %s, %s\n", name, strerror(errno));
                name[0] = '\0';
            } else {
                LOGD("%s: %s", args[i], name);
                printf("%s", name);
            }
        }
    }
}
