include(CTest)
add_executable(ALL
    TupleTests.cpp
    ColorTests.cpp
    CanvasTests.cpp
    MatricesTests.cpp
    TransformationsTests.cpp
    RayTests.cpp
    SphereTests.cpp
    LightTests.cpp
    WorldTests.cpp
    IntersectionTests.cpp
    CameraTests.cpp
    PlaneTests.cpp
)
target_link_libraries(ALL ray-tracer-lib)
target_link_libraries(ALL ${GTEST_LIBRARIES})
target_link_libraries(ALL GTest::gmock_main)


target_include_directories(ALL PUBLIC ${CMAKE_SOURCE_DIR}/src)

add_test(NAME AllTests COMMAND ALL)