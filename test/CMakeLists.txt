project(CRrendererTest)

function(createTest DIRECTORY NAME)
    set(TEST_NAME test_${NAME})
    add_executable(${TEST_NAME} ${DIRECTORY}/${NAME}.cpp)
    target_include_directories(${TEST_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
    target_link_libraries(${TEST_NAME} libCRrenderer ${SDL2_LIBRARIES})
    add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
endfunction() # createTest

createTest(utils testRay)
createTest(utils testTransformation)
createTest(components testSphereObject)
createTest(components testTriangleMeshObject)
createTest(components testSurfaceObject)
createTest(components testBBox)
createTest(components testCamera)
createTest(material testMirrorBSDF)