#ifndef UTILS_HPP
#define URILS_HPP

#include <string>
#include <sys/stat.h>

std::string file_permission(const struct stat& file_stat);

#endif