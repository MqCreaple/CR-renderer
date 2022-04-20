#pragma once

#include <iostream>
#include <string>
#include <cstdio>
#include <cstdarg>

class Log {
public:
    /**
     * @brief default output stream of the logger
     */
    static std::ostream& defaultOStream;
    /**
     * @brief log normal information
     * @param message message
     */
    static void info(const char* message);
    /**
     * @brief log warnings
     * @param message warning message
     */
    static void warn(const char* message);
    /**
     * @brief log fatal error and exit the program
     * @param message error message
     */
    static void error(int errorCode, const char* message);
};