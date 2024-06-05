add_executable(clock
    Clock.cpp
)
target_include_directories(clock PUBLIC ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(clock ray-tracer-lib)