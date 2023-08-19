#include "datetime.h"
#include <ctime>
#include <sstream>
#include <iomanip>

std::string get_current_datetime(){
    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);

    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y_%m_%d_%H_%M_%S");
    return oss.str();
}