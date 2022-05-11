#include "scene/Scene.h"

Scene::Scene(): primaryCam(), list(new ObjectList) {}
Scene::Scene(const Camera& camera, AmbientLight* ambientLight)
    : primaryCam(camera), list(new ObjectList), ambientLight(ambientLight) {}

Camera& Scene::getPrimaryCamera() {
    return primaryCam;
}

ObjectList* Scene::getObjects() const {
    return list;
}

std::vector<PointLight*>& Scene::getLights() {
    return lights;
}

AmbientLight* Scene::getAmbientLight() const {
    return ambientLight;
}

Scene::~Scene() {
    delete list;
}
