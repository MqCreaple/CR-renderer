add_library(CRrendererLib
    components/ThreeDObject.cpp
    components/TracableObject.cpp
    components/TriangleMeshObject.cpp
    components/SphereObject.cpp
    components/BBox.cpp
    components/Camera.cpp
    material/MirrorBSDF.cpp
    scene/Scene.cpp
    renderer/Renderer.cpp
    renderer/RayTracingRenderer.cpp
    utils/Log.cpp
    utils/Ray.cpp
    utils/Transformation.cpp
    utils/Random.cpp
)

add_executable(CRrenderer main.cpp)
target_link_libraries(CRrenderer ${SDL2_LIBRARIES} CRrendererLib)