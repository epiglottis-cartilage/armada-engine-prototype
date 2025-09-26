#include <iostream>
#include <string>
#include <source_location> // C++20

class dbgJellyfish {
public:
static void debug_log(const std::string& msg,
               const std::source_location location = std::source_location::current())
{
    std::cout << "[DEBUG] " << msg
              << " (" << location.file_name()
              << ":" << location.line()
              << " in " << location.function_name()
              << ")\n";
}


};
