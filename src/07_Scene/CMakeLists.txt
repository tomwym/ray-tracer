add_executable(scene
    Scene.cpp
)
target_include_directories(scene PUBLIC ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(scene ray-tracer-lib)