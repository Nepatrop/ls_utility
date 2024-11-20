#include <iostream>
#include <dirent.h>
#include <vector>
#include <iomanip>
#include <pwd.h>
#include <grp.h>
#include <ctime>
#include <algorithm>
#include "ls.hpp"
#include "utils.cpp"

const char* months[] = {"янв", "фев", "мар", "апр", "май", "июн", "июл", "авг", "сен", "окт", "ноя", "дек"};

bool compare_name(const FileInfo& fir, const FileInfo& sec) {
    return fir.name < sec.name;
}

void list_directory(const std::string& path, bool l) {
    DIR* dir = opendir(path.c_str());
    
    if (dir == nullptr) {
        std::cerr << "Cannot open directory: " << path << std::endl;
        return;
    }

    struct dirent* dirent;
    std::vector<FileInfo> files;
    size_t nlink_tab = 0;
    size_t user_tab = 0;
    size_t group_tab = 0;
    size_t size_tab = 0;

    while ((dirent = readdir(dir)) != nullptr) {
        if (dirent->d_name[0] != '.') {
            std::string file = dirent->d_name;
            std::string full_path = path + "/" + file;
            struct stat file_stat;
            if (stat(full_path.c_str(), &file_stat) == 0) {
                files.push_back({file, file_stat});

                size_t nlink_width = std::to_string(file_stat.st_nlink).length();
                if (nlink_width > nlink_tab) nlink_tab = nlink_width;
                
                size_t user_width  = std::string(getpwuid(file_stat.st_uid)->pw_name).length();
                if (user_width > user_tab) user_tab = user_width;
                
                size_t group_width  = std::string(getgrgid(file_stat.st_gid)->gr_name).length();
                if (group_width > group_tab) group_tab = group_width;
                
                size_t size_width  = std::to_string(file_stat.st_size).length();
                if (size_width > size_tab) size_tab = size_width;
            }
        }
    }
    closedir(dir);

    std::sort(files.begin(), files.end(), compare_name);

    for (const auto& file : files) {
        if (l) {
            std::cout << file_permission(file.stat) << " ";
            
            std::cout << std::setw(nlink_tab) << file.stat.st_nlink << " ";
            
            std::cout << std::setw(user_tab) << getpwuid(file.stat.st_uid)->pw_name << " ";
            
            std::cout << std::setw(group_tab) << getgrgid(file.stat.st_gid)->gr_name << " ";
            
            std::cout << std::setw(size_tab) << file.stat.st_size << " ";
            
            std::tm* timeinfo = std::localtime(&file.stat.st_mtime);
            std::cout << months[timeinfo->tm_mon] << " ";
            
            int day = timeinfo->tm_mday;
            if (day < 10) {
                std::cout << " " << day << " ";
            } else {
                std::cout << day << " ";
            }

            std::cout << timeinfo->tm_hour << ":";

            int min = timeinfo->tm_min;
            if (min < 10) {
                std::cout << "0" << min << " ";
            } else {
                std::cout << min << " ";
            }

            std::cout << file.name << std::endl;
        }
        else {
            std::cout << file.name << "  ";
        }
    }

    if (!l) {
        std::cout << std::endl;
    }
}