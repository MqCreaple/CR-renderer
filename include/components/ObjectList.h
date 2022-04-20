#pragma once

#include "components/TracableObject.h"
#include <vector>
#include <memory>

class ObjectList: public TracableObject {
public:
private:
    std::vector<std::shared_ptr<TracableObject>> objects;
};