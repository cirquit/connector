#ifndef UTIL_H
#define UTIL_H

#include <iostream>
#include <functional>

#if !defined(DEBUG_MODE)
    #error DEBUG_MODE has to be defined through 'cmake .. -DDEBUG_MODE=[0/1]'
#endif

#if DEBUG_MODE
#define DEBUG_MSG(msg) std::cerr << "[INFO] " << msg << '\n'
#else
#define DEBUG_MSG(msg)
#endif // DEBUG_MODE (in [package-name]/CMakeLists.txt)
namespace connector {

    enum CONNECTOR_TYPE : size_t { TCP = 0, UDP = 1 };
}
#endif  // UTIL_H
