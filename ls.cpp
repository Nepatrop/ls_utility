#include "ls.hpp"
#include <iostream>
#include <dirent.h>
#include <vector>

void list_directory(const std::string& path) {
    DIR* dir = opendir(path.c_str());
    if (!dir) {
        std::cerr << "Cannot open directory: " << path << std::endl;
        return;
    }

    struct dirent* dirent;
    std::vector<std::string> files;

    while ((dirent = readdir(dir))) {
        if (dirent->d_name[0] != '.') {
            files.push_back(dirent->d_name);
        }
    }
    closedir(dir);

    int size = files.size() - 1;
    for (int i = 0; i < size; i++){
        std::cout << files[i] << "  ";
    }
    std::cout << files[size] << std::endl;
}