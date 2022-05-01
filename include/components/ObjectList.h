#pragma once

#include "components/Tracable.h"
#include <vector>

class ObjectList: public Tracable {
public:
    ObjectList();
    ObjectList(const std::vector<Tracable*>& list);
    void add(Tracable& obj);

    HitResult intersect(const Ray& ray, float tMin = DEFAULT_T_MIN, float tMax = DEFAULT_T_MAX) const override;
private:
    std::vector<Tracable*> objects;
};