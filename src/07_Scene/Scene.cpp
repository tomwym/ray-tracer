#include "Canvas.h"
#include "Point.h"
#include "Ray.h"
#include "Sphere.h"
#include "Light.h"
#include "Transformations.h"
#include "World.h"
#include "Camera.h"

#include <fstream>
#include <numbers>

namespace nums = std::numbers;

int main() {
    std::unique_ptr<Light> source{std::make_unique<Light>(Point{-10,10,-10},Color{1,1,1})};
    World world{std::move(source)};

    Matrix4d transform{ViewTransform(
        Point{0,1.5,-5},
        Point{0,1,0},
        Vector{0,1,0}
    )};
    Camera camera{300,150,nums::pi/3.f,transform};
    {
        // floor
        Matrix4d transform{Transformations::Scaling(10,0.01,10)};
        Material_t mat;
        mat.color = Color{1,0.9,0.9};
        mat.specular = 0.f;
        std::unique_ptr<Geometry> sphere{std::make_unique<Sphere>(transform, mat)};
        world.AddGeometry(std::move(sphere));
    }
    {
        // left wall
        Matrix4d transform{
            Transformations::Translation(0,0,5) *
            Transformations::RotationY(-nums::pi/4.f) *
            Transformations::RotationX(nums::pi/2.f) *
            Transformations::Scaling(10,0.01,10)
        };
        Material_t mat;
        std::unique_ptr<Geometry> sphere{std::make_unique<Sphere>(transform, mat)};
        world.AddGeometry(std::move(sphere));
    }
    {
        // right wall
        Matrix4d transform{
            Transformations::Translation(0,0,5) *
            Transformations::RotationY(nums::pi/4.f) *
            Transformations::RotationX(nums::pi/2.f) *
            Transformations::Scaling(10,0.01,10)
        };
        Material_t mat;
        std::unique_ptr<Geometry> sphere{std::make_unique<Sphere>(transform, mat)};
        world.AddGeometry(std::move(sphere));
    }
    {
        // middle sphere
        Matrix4d transform{Transformations::Translation(-0.5,1,0.5)};
        Material_t mat;
        mat.color = Color{0.1,1,0.5};
        mat.diffuse = 0.7f;
        mat.specular = 0.3f;
        std::unique_ptr<Geometry> sphere{std::make_unique<Sphere>(transform, mat)};
        world.AddGeometry(std::move(sphere));
    }
    {
        // right sphere
        Matrix4d transform{
            Transformations::Translation(1.5,0.5,-0.5) *
            Transformations::Scaling(0.5,0.5,0.5)
        };
        Material_t mat;
        mat.color = Color{0.5,1,0.1};
        mat.diffuse = 0.7f;
        mat.specular = 0.3f;
        std::unique_ptr<Geometry> sphere{std::make_unique<Sphere>(transform, mat)};
        world.AddGeometry(std::move(sphere));
    }
    {
        // left sphere
        Matrix4d transform{
            Transformations::Translation(-1.5,0.33,-0.75) *
            Transformations::Scaling(0.33,0.33,0.33)
        };
        Material_t mat;
        mat.color = Color{1,0.8,0.1};
        mat.diffuse = 0.7f;
        mat.specular = 0.3f;
        std::unique_ptr<Geometry> sphere{std::make_unique<Sphere>(transform, mat)};
        world.AddGeometry(std::move(sphere));
    }

    Canvas canvas{camera.Render(world)};
    std::ofstream file{"res/scene.ppm", std::ios::trunc};
    file << canvas.ToPPM();
}