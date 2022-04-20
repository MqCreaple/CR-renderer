#include "scene/Scene.h"

Scene::Scene(): primaryCam(), objects() {}
Scene::Scene(const Camera& camera): primaryCam(camera), objects() {}

void Scene::addObject(const std::shared_ptr<TracableObject>& obj) {
    objects.push_back(obj);
}

Camera Scene::getPrimaryCamera() const {
    return primaryCam;
}
std::shared_ptr<TracableObject> Scene::getObject(int i) const {
    return objects[i];
}