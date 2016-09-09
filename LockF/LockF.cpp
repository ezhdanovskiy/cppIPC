#include "Logger.h"

#include <err.h>
#include <errno.h>
#include <fcntl.h>
#include <cstring>


int main(int argc, char **argv) {
    std::string fname("file.lock");
    int mode = 0666;
    int fd;
    switch (fork()) {
        case -1: {
            err(1, "fork");
        }
        case 0: {
            usleep(100000);
            int flags = O_RDWR;
//            int flags = O_RDONLY; // do not lock
            fd = ::open(fname.c_str(), flags, mode);
            LOG("READER  ::open('" << fname << "', " << flags << ", " << mode << ") return " << fd);
            if (-1 == fd) {
                LOG("open error(" << errno << "): " << strerror(errno));
            }

            LOG("before F_LOCK")
            int res = lockf(fd, F_LOCK, 0);
            if (-1 == res) {
                LOG("open error(" << errno << "): " << strerror(errno));
            }

            LOG("after lock")
            break;
        }
        default: {
            int flags = O_WRONLY | O_APPEND | O_CREAT | O_NONBLOCK;
            fd = ::open(fname.c_str(), flags, mode);
            LOG("WRITER ::open('" << fname << "', " << flags << ", " << mode << ") return " << fd);
            if (-1 == fd) {
                LOG("open error(" << errno << "): " << strerror(errno));
            }

            LOG("before F_LOCK")
            int res = lockf(fd, F_LOCK, 0);
            if (-1 == res) {
                LOG("open error(" << errno << "): " << strerror(errno));
            }

            LOG("after lock")

            sleep(3);
            break;
        }
    }
    LOG("F_ULOCK");
    close(fd);
    LOG("close(" << fd << ")");
    close(fd);
    return 0;
}
