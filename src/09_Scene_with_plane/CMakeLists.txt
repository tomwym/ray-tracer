add_executable(scene_with_plane
    Scene.cpp
)
target_include_directories(scene_with_plane PUBLIC ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(scene_with_plane ray-tracer-lib)