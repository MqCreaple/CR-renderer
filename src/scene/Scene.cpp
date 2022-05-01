#include "scene/Scene.h"

Scene::Scene(): primaryCam(), list(new ObjectList) {}
Scene::Scene(const Camera& camera): primaryCam(camera), list(new ObjectList) {}

Camera& Scene::getPrimaryCamera() {
    return primaryCam;
}

ObjectList* Scene::getObjects() const {
    return list;
}

std::vector<PointLight*>& Scene::getLights() {
    return lights;
}

Scene::~Scene() {
    delete list;
}
