add_executable(sphere
    Sphere.cpp
)
target_include_directories(sphere PUBLIC ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(sphere ray-tracer-lib)