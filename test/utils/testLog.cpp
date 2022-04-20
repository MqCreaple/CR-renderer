#include "TestInclude.h"
#include "utils/Log.h"

int main() {
    Log::info("This is an info message for testing.");
    Log::warn("This is a warning message for testing.");
    Log::error(0, "This is an error message for testing.");
}