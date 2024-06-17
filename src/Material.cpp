#include "Material.h"
#include "Light.h"
#include "Point.h"
#include "Vector.h"

auto Lighting(
    const Material_t& mat,
    const Light& light,
    const Point& pos,
    const Vector& eyev,
    const Vector& normalv,
    const bool in_shadow) -> Color
{
    Color effective_color{mat.color * light.intensity};
    Vector lightv{(light.position - pos).Normalize()};
    Color ambient{effective_color * mat.ambient};

    if(in_shadow)
        return ambient;

    Color black{0,0,0};
    Color diffuse{black};
    Color specular{black};
    float light_dot_normal{lightv.Dot(normalv)};
    if (light_dot_normal >= 0) {
        diffuse = effective_color * mat.diffuse * light_dot_normal;
        Vector reflectv{Vector{-lightv}.Reflect(normalv)};
        float reflect_dot_eye{reflectv.Dot(eyev)};
        if (reflect_dot_eye > 0) {
            float factor{std::pow(reflect_dot_eye, mat.shininess)};
            specular = light.intensity * mat.specular * factor;
        }
    }
    return ambient + diffuse + specular;
}