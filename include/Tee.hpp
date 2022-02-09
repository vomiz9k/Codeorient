#include <string>

class Tee {
public: 
    Tee(const char* file_name, bool inplace);
    void Process();

private:
    enum class Syscall {
        OPEN,
        WRITE,
        READ,
        CLOSE
    };

    static const size_t BUFFER_LEN = 4096;

    void CheckCError(int status, Syscall syscall);
    int fd_;

    void Write(int fd, char* buffer, size_t bytes);
    ssize_t Read(char* buffer);
};