add_executable(projectile-renderer
    Projectile.cpp
    ProjectileRenderer.cpp
)
target_include_directories(projectile-renderer PUBLIC ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(projectile-renderer ray-tracer-lib)