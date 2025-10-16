#pragma once

//cpp20 includes
#include <string>
#include <filesystem>
#include <iostream>
#include <vector>
#include <optional>
#include <memory>

#define NAMESPACE_BEGIN namespace fleet {
#define NAMESPACE_END }

;

#define FLEET_API


typedef std::string string;


using std::vector;
using std::shared_ptr;

namespace fs = std::filesystem;
////globaly replace new with EASTL version

