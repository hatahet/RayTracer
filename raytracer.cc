#include <algorithm>

#include <cmath>

#include "raytracer.h"

namespace {

raytracer::Color background(0, 0, 0);
raytracer::Color default_color(0, 0, 0);

const int kMaxDepth = 5;

}  // namespace

namespace raytracer {

std::vector<ISect> RayTracer::GetIntersections(const Ray& ray,
                                               const Scene& scene) const {
  auto ret(scene.Intersect(ray));
  if (ret.size() <= 1)
    return ret;

  std::sort(ret.begin(), ret.end(), [](const ISect& s1, const ISect& s2) {
    return s1.dist < s2.dist;
  });
  return ret;
}

double RayTracer::CastTestRay(const Ray& ray, const Scene& scene) const {
  auto intersections(GetIntersections(ray, scene));
  if (intersections.size() == 0)
    return 0.0;
  return intersections[0].dist;
}

Color RayTracer::TraceRay(const Ray& ray, const Scene& scene, int depth) const {
  auto intersections(GetIntersections(ray, scene));
  if (intersections.size() == 0)
    return background;
  return Shade(intersections[0], scene, depth);
}

Color RayTracer::GetNaturalColor(const SceneObject& thing, const Vector3& pos,
                                 const Vector3& normal, const Vector3& rd,
                                 const Scene& scene) const {
  Color ret(0, 0, 0);
  for (auto it = scene.lights.cbegin(); it != scene.lights.cend(); ++it) {
    Vector3 ldis(it->pos - pos);
    Vector3 livec(ldis.Normal());
    double neat_isect = CastTestRay(Ray(pos, livec), scene);
    bool in_shadow = !((neat_isect > ldis.Magnitude()) || (neat_isect == 0));
    if (!in_shadow) {
      double illum = livec.Dot(normal);
      Color lcolor = illum > 0 ? illum * it->color : Color(0, 0, 0);
      double specular = livec.Dot(rd.Normal());
      Color scolor = specular > 0 ? std::pow(specular, thing.surface.roughness) * it->color : Color(0, 0, 0);
      ret = ret + ((thing.surface.Diffuse(pos) * lcolor) + (thing.surface.Specular(pos) * scolor));
    }
  }
  return ret;
}

Color RayTracer::GetReflectionColor(const SceneObject& thing, const Vector3& pos,
                                    const Vector3& rd, const Scene& scene,
                                    int depth) const {
  return thing.surface.Reflect(pos) * TraceRay(Ray(pos, rd), scene, depth);
}

Color RayTracer::Shade(const ISect& isect, const Scene& scene, int depth) const {
  auto d = isect.ray.dir;
  auto pos = (isect.dist*isect.ray.dir) + isect.ray.start;
  auto normal = isect.thing->Normal(pos);
  auto reflect_dir = (d) - ((2*normal.Dot(d))*(normal));
  Color ret(default_color);
  ret = (ret)+(GetNaturalColor(*isect.thing, pos, normal, reflect_dir, scene));
  if (depth > kMaxDepth)
    return ret + Color(0.5, 0.5, 0.5);
  return ret + (GetReflectionColor(*isect.thing, (pos)+(0.001*reflect_dir), reflect_dir, scene, depth));
}

double RayTracer::RecenterX(double x) const {
  return (x - width_ / 2.0) / (2.0 * width_);
}

double RayTracer::RecenterY(double y) const {
  return -(y - height_ / 2.0) / (2.0 * height_);
}

Vector3 RayTracer::GetPoint(double x, double y, const Camera& camera) const {
  return ((camera.forward) + ((RecenterX(x))*(camera.right) + (RecenterY(y))*(camera.up))).Normal();
}

void RayTracer::Render(const Scene& scene) {
  for (int y = 0; y < height_; ++y) {
    for (int x = 0; x < width_; ++x) {
      Color color(TraceRay(Ray(scene.camera.pos, GetPoint(x, y, scene.camera)), scene, 0));
      image_.SetPixel(x, y, color);
    }
  }
}

}  // namespace raytracer
