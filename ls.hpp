#ifndef LS_HPP
#define LS_HPP

#include <string>
#include <sys/stat.h>

struct FileInfo {
    std::string name;
    struct stat stat;
};

bool compare_name(const FileInfo& fir, const FileInfo& sec);
bool compare_name_reverse(const FileInfo& fir, const FileInfo& sec);
void list_directory(const std::string& path, bool l, bool r);

#endif