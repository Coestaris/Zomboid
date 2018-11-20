#include "utils.h"

bool Utils::fileExists(std::string str)
{
    struct stat buffer;
    return (stat (str.c_str(), &buffer) == 0);
}
