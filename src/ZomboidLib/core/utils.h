#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

#include <string>
#include <sys/stat.h>

class Utils
{
public:
    static bool fileExists(std::string);
};

#endif // UTILS_H_INCLUDED
