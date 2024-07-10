#include "Geometry.h"

GeometryPropertiesImpl::GeometryPropertiesImpl(const Matrix4d& transform, const Material_t& mat)
: transform{transform}
, material{mat}
{}

auto GeometryPropertiesImpl::Transform() const -> Matrix4d {
    return transform;
}

auto GeometryPropertiesImpl::Transform(const Matrix4d& other) -> void {
    transform = other;
}

auto GeometryPropertiesImpl::Material() const -> Material_t {
    return material;
}

auto GeometryPropertiesImpl::Material() -> Material_t& {
    return material;
}

auto GeometryPropertiesImpl::Material(const Material_t& mat) -> void {
    material = mat;
}
