#include <Tee.hpp>

#include <unistd.h>
#include <fcntl.h>

#include <stdexcept>
#include <errno.h>

Tee::Tee(const char* file_name, bool append_mode) {
    int flags =  O_CREAT;

    if (append_mode) {
        flags |= O_APPEND | O_RDWR;
    } else {
        flags |= O_WRONLY | O_TRUNC;
    }

    fd_ = open(file_name, flags, 0644);
    CheckCError(fd_, Syscall::OPEN);
}

void Tee::Process() {
    char* buffer = static_cast<char*>(calloc(sizeof(char), BUFFER_LEN));
    ssize_t bytes = Read(buffer);

    while(bytes > 0) {
        Write(fd_, buffer, bytes);;
        Write(STDOUT_FILENO, buffer, bytes);

        bytes = Read(buffer);
    }

    CheckCError(close(fd_), Syscall::CLOSE);
}

void Tee::Write(int fd, char* buffer, size_t bytes) {
    ssize_t bytes_wrote = write(fd, buffer, bytes);
    CheckCError(bytes_wrote, Syscall::WRITE);
}

ssize_t Tee::Read(char* buffer) {
    ssize_t bytes = read(STDIN_FILENO, buffer, BUFFER_LEN - 1);
    CheckCError(bytes, Syscall::READ);
    return bytes;
}

void Tee::CheckCError(int status, Syscall syscall) {
    if (status == -1) {
        std::string syscall_name;

        #define CASE(SYSCALL) \
            case Syscall::SYSCALL: \
                syscall_name = #SYSCALL;

        switch(syscall) {
            CASE(OPEN)
            CASE(WRITE)
            CASE(READ)
            CASE(CLOSE)
        }
        #undef CASE

        throw std::runtime_error(
            "Error code: " + std::to_string(errno) + " while processing " + syscall_name + " function.\n"
        );
    }
}

