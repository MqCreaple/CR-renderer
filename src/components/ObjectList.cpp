#include "components/ObjectList.h"

ObjectList::ObjectList(): objects() {}

ObjectList::ObjectList(const std::vector<Tracable*>& list): objects(list) {}

void ObjectList::add(Tracable& obj) {
    objects.push_back(&obj);
}

Tracable::HitResult ObjectList::intersect(const Ray& ray, float tMin, float tMax) const {
    HitResult result;
    result.t = INFINITY;
    for(auto it = objects.begin(); it != objects.end(); ++it) {
        HitResult tmp = (*it)->intersect(ray, tMin, tMax);
        if(tmp.valid && tmp.t < result.t) {
            result = tmp;
        }
    }
    return result;
}