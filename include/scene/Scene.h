#pragma once

#include "components/ThreeDObject.h"
#include "components/TriangleMeshObject.h"
#include "components/Camera.h"
#include <vector>
#include <memory>

class Scene {
public:
    Scene();
    Scene(const Camera& camera);
    void addObject(const std::shared_ptr<TracableObject>& object);

    Camera getPrimaryCamera() const;
    std::shared_ptr<TracableObject> getObject(int i) const;
    ~Scene();
private:
    Camera primaryCam;
    std::vector<std::shared_ptr<TracableObject>> objects;
};