add_library(ray-tracer-lib
    Constvals.cpp
    TupleF.cpp
    Projectile.cpp
    Transformations.cpp
)

add_executable(projectile-renderer
    ProjectileRenderer.cpp
)
target_link_libraries(projectile-renderer ray-tracer-lib)