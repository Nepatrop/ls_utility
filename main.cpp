#include  <iostream>
#include <getopt.h>
#include "ls.cpp"

int main(int argc, char* argv[]) {
    std::string directory = ".";
    int opt;
    bool l = false;
    bool r = false;
    bool h = false;

    while ((opt = getopt(argc, argv, "lrh")) != -1) {
        switch (opt) {
            case 'l':
                l = true;
                break;
            case 'r':
                r = true;
                break;
            case 'h':
                h = true;
                break;
            default:
                return 0;
        }
    }

    if (optind < argc){
        directory = argv[optind];
    }

    list_directory(directory, l, r, h);

    return 0;
}