#include  <iostream>
#include <getopt.h>
#include "ls.cpp"

int main(int argc, char* argv[]) {
    std::string directory = ".";
    int opt;
    bool l;
    bool r;

    while ((opt = getopt(argc, argv, "lr")) != -1) {
        switch (opt) {
            case 'l':
                l = true;
                break;
            case 'r':
                r = true;
                break;
            default:
                std::cerr << "Error" << std::endl;
        }
    }

    if (optind < argc){
        directory = argv[optind];
    }

    list_directory(directory, l, r);

    return 0;
}