add_library(libCRrenderer
    components/ThreeDObject.cpp
    components/Tracable.cpp
    components/VisibleObject.cpp
    components/TriangleMeshObject.cpp
    components/SphereObject.cpp
    components/SurfaceObject.cpp
    components/ObjectList.cpp
    components/BBox.cpp
    components/Camera.cpp
    light/PointLight.cpp
    material/BSDF.cpp
    material/MirrorBSDF.cpp
    material/DiffuseBSDF.cpp
    scene/Scene.cpp
    renderer/Renderer.cpp
    renderer/RayTracingRenderer.cpp
    utils/Ray.cpp
    utils/Transformation.cpp
    utils/Random.cpp
)

add_executable(CRrenderer main.cpp)
target_link_libraries(CRrenderer libCRrenderer ${SDL2_LIBRARIES})