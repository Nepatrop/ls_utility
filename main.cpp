#include  <iostream>
#include <getopt.h>
#include "ls.cpp"

int main(int argc, char* argv[]) {
    bool l;
    std::string directory = ".";
    int opt;

    while ((opt = getopt(argc, argv, "l")) != -1) {
        switch (opt) {
            case 'l':
                l = true;
                break;
            default:
                std::cerr << "Error" << std::endl;
        }
    }

    if (optind < argc){
        directory = argv[optind];
    }

    list_directory(directory, l);

    return 0;
}