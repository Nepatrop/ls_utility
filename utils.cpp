#include "utils.hpp"

std::string file_permission(const struct stat& file_stat) {
    const char* perms[] = {"---", "--x", "-w-", "-wx", "r--", "r-x", "rw-", "rwx"};
    std::string permissions = (S_ISDIR(file_stat.st_mode) ? "d" : "-");

    permissions += perms[(file_stat.st_mode & S_IRWXU) >> 6];
    permissions += perms[(file_stat.st_mode & S_IRWXG) >> 3];
    permissions += perms[(file_stat.st_mode & S_IRWXO)];

    return permissions;
}