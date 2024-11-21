#include <cmath>
#include "utils.hpp"

std::string file_permission(const struct stat& file_stat) {
    const char* perms[] = {"---", "--x", "-w-", "-wx", "r--", "r-x", "rw-", "rwx"};
    std::string permissions = (S_ISDIR(file_stat.st_mode) ? "d" : "-");

    permissions += perms[(file_stat.st_mode & S_IRWXU) >> 6];
    permissions += perms[(file_stat.st_mode & S_IRWXG) >> 3];
    permissions += perms[(file_stat.st_mode & S_IRWXO)];

    return permissions;
}

std::string file_size(off_t size, bool h){
    if (h) {
        const char* units[] = {"", "K", "M", "G", "T", "P"};
        int rank = 0;
        double value = static_cast<double>(size);

        while (value >= 1024.0 && rank < 5) {
            value /= 1024.0;
            rank++;
        }

        int remainder = std::round(value * 10) / 10.0;
        int integer = static_cast<int>(value);
        double sec_val = value - integer;

        if (sec_val == 0.0) {
            if (rank > 0){
                return std::to_string(integer) + ",0" + units[rank];
            }
            return std::to_string(integer) + units[rank];
        } else {
            int result_sec = static_cast<int>(sec_val * 10) + 1;
            if (result_sec == 10){
                return std::to_string(integer + 1) + units[rank];
            }

            return std::to_string(integer) + "," + std::to_string(result_sec) + units[rank];
        }
        return std::to_string(value) + units[rank];
    } else {
        return std::to_string(size);
    }
}