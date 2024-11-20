#include  <iostream>
#include "ls.cpp"

int main(int argc, char* argv[]) {
    std::string directory = ".";

    if (argc > 1){
        directory = argv[1];
    }

    list_directory(directory);
}