#include "Logger.h"

#include <fstream>
#include <sstream>
#include <iconv.h>
#include <err.h>
#include <stdlib.h>
#include <sys/wait.h>

std::string convert(const std::string &in) {
    std::string out(in.size() * 2, ' ');
    LOG1(in.size());
    LOG1(out.size());
    iconv_t cd = iconv_open("utf8", "cp1251");
    if (cd == (iconv_t)(-1)) {
        err(1, "iconv_open");
    }
    size_t inbytesleft = in.size();
    char *outbuf = &out[0];
    size_t outbytesleft = out.size();
#if defined(__linux__)
    char *inbuf = const_cast<char*>(&in[0]);
    iconv(cd, &inbuf, &inbytesleft, &outbuf, &outbytesleft);
#else
    const char *inbuf = &in[0];
    iconv(cd, &inbuf, &inbytesleft, &outbuf, &outbytesleft);
#endif
    iconv_close(cd);
    out.resize(out.size() - outbytesleft);
    LOG1(out.size());
    return out;
}

int main() {
    int pipefd[2];
    if(pipe(pipefd) == -1) {
        err(1, "pipe");
    }

    int pid;
    int rv;
    switch(pid = fork()) {
        case -1: {
            err(1, "fork");
        }
        case 0: {
            LOG("CHILD");
            close(pipefd[1]);
            std::ofstream fileOut("out.utf8.txt");
            const size_t buffSize = 0x1000;
            char buff[buffSize + 1];
            ssize_t wasRead = buffSize;
            int wasWritten = 0;
            while (wasRead == buffSize) {
                wasRead = read(pipefd[0], buff, buffSize);
                buff[wasRead] = 0;
                fileOut << buff;
                wasWritten += wasRead;
            }
            LOG1(wasWritten);
            close(pipefd[0]);
            exit(0);
        }
        default: {
            LOG("PARENT");
            close(pipefd[0]);
            std::ifstream fileIn("in.cp1251.txt");
            std::stringstream sin;
            sin << fileIn.rdbuf();
            std::string out = convert(sin.str());
            write(pipefd[1], out.c_str(), out.size());
            close(pipefd[1]);
            int status;
            waitpid(pid, &status, 0);
            LOG1(status);
        }
    }
    return 0;
}
