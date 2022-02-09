#include <Tee.hpp>

#include <iostream>
#include <string.h>

void PrintHelp() {
    std::cout << "Usage: ./tee [-a] <file>\n\n";
    std::cout << "The tee command reads its standart input until end-of-file, writing a copy of the input to standart outputand to the file specified as argument.\n\n";
    std::cout << "Options:\n";
    std::cout << "-a\tOpen file in append mode.\n";
    std::cout << "-h\tShow help.\n";
}

std::pair<char*, bool> CommandLineParse(int argc, char* argv[]) {
    if (argc < 2 || argc > 3 || strcmp(argv[1], "-h") == 0 ||
        (argc == 3 && strcmp(argv[1], "-a"))) {
        PrintHelp();
        exit(0);
    }

    bool append_mode = (argc == 3);
    char* file_name = append_mode ? argv[2] : argv[1];
    return std::pair(file_name, append_mode);
}

int main(int argc, char* argv[]) {
    auto parsed_args = CommandLineParse(argc, argv);
    char* file_name = parsed_args.first;
    bool append_mode = parsed_args.second;

    try {
        Tee tee(file_name, append_mode);
        tee.Process();
    } catch(const std::runtime_error& err) {
        std::cerr << err.what();
    }
}