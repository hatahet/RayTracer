#include "utils.h"

namespace raytracer {

// Camera

Camera::Camera(const Vector3& position, const Vector3& look_at)
    : pos(position),
      forward((look_at - pos).Normal()),
      right(1.5 * (forward.Cross(Vector3(0, -1, 0))).Normal()),
      up(1.5 * (forward.Cross(right)).Normal()) { }


// Sphere

bool Sphere::Intersect(const Ray& ray, ISect* isect) const {
  Vector3 eo(center - ray.start);
  double v = eo.Dot(ray.dir);
  double dist;
  if (v < 0) {
    dist = 0.0;
  } else {
    double disc = radius*radius - (eo.Dot(eo) - v*v);
    dist = disc < 0.0 ? 0.0 : v - std::sqrt(disc);
  }

  if (dist == 0.0)
    return false;

  isect->thing = this;  // Careful of potential segfaults. If *this is
                        // is stack-allocated it must be in the same scope
                        // as |isect|.  Possible improvement is to do away with
                        // thing ptr and have a member with only required
                        // properties of object being intersected copied over.
  isect->ray = ray;
  isect->dist = dist;
  return true;
}

Vector3 Sphere::Normal(const Vector3& pos) const {
  return (pos - center).Normal();
}


// Plane

bool Plane::Intersect(const Ray& ray, ISect* isect) const {
  double denominator = normal.Dot(ray.dir);
  if (denominator >= 0.0)
    return false;

  isect->thing = this;
  isect->ray = ray;
  isect->dist = (normal.Dot(ray.start) + offset) / (-denominator);
  return true;
}

Vector3 Plane::Normal(const Vector3& pos) const {
  return normal;
}


// Scene

std::vector<ISect> Scene::Intersect(const Ray& ray) const {
  std::vector<ISect> ret;  // XXX: ISect*
  ISect isect;
  for (auto it = things.cbegin(); it != things.cend(); ++it) {
    if ((*it)->Intersect(ray, &isect))
      ret.push_back(isect);
  }
  return ret;
}

}  // namesace raytracer
