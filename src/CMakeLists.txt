add_library(ray-tracer-lib
    TupleF.cpp
    Projectile.cpp
    Constvals.cpp
)

add_executable(projectile-renderer
    ProjectileRenderer.cpp
)
target_link_libraries(projectile-renderer ray-tracer-lib)