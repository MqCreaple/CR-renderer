#pragma once

#include "components/ThreeDObject.h"
#include "components/ObjectList.h"
#include "components/Camera.h"
#include "light/PointLight.h"
#include <vector>
#include <functional>

class Scene {
public:
    Scene();
    Scene(const Camera& camera);

    Camera& getPrimaryCamera();
    ObjectList* getObjects() const;
    std::vector<PointLight*>& getLights();
    ~Scene();
private:
    Camera primaryCam;
    ObjectList* list;
    std::vector<PointLight*> lights;
};