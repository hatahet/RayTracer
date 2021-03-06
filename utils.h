#ifndef UTILS_H_
#define UTILS_H_
#pragma once

#include <functional>
#include <vector>

#include "color.h"
#include "vector.h"

namespace raytracer {

struct Ray {
  Ray();
  Ray(const Vector3& s, const Vector3& d);

  Vector3 start;
  Vector3 dir;
};

inline Ray::Ray() : start(Vector3(0, 0, 0)), dir(Vector3(0, 0, 0)) { }
inline Ray::Ray(const Vector3& s, const Vector3& d) : start(s), dir(d) { }

struct Light {
  Light(const Vector3& pos, const Color& color);

  Vector3 pos;
  Color color;
};

inline Light::Light(const Vector3& v, const Color& c) : pos(v), color(c) { }

class Camera {
 public:
  Camera(const Vector3& pos, const Vector3& look_at);

  Vector3 pos;
  Vector3 forward;
  Vector3 right;
  Vector3 up;
};

struct Surface {
  std::function<Color(const Vector3&)> Diffuse;
  std::function<Color(const Vector3&)> Specular;
  std::function<double(const Vector3&)> Reflect;
  double roughness;
};

class SceneObject;

struct ISect {
  const SceneObject* thing;
  Ray ray;
  double dist;
};

class SceneObject {
 public:
  SceneObject(const Surface& s) : surface(s) { }
  virtual ~SceneObject() {}
  virtual bool Intersect(const Ray& ray, ISect* isect) const = 0;
  virtual Vector3 Normal(const Vector3& pos) const = 0;

  Surface surface;
};

class Sphere : public SceneObject {
public:
  Sphere(const Surface& surface, const Vector3& center, double radius);
  ~Sphere();

  bool Intersect(const Ray& ray, ISect* isect) const override;
  Vector3 Normal(const Vector3& pos) const override;

  Vector3 center;
  double radius;
};

inline Sphere::Sphere(const Surface& surface, const Vector3& c, double r)
    : SceneObject(surface), center(c), radius(r) { }

inline Sphere::~Sphere() { }

class Plane : public SceneObject {
 public:
  Plane(const Surface& surface, const Vector3& normal, double offset);
  ~Plane();

  bool Intersect(const Ray& ray, ISect* isect) const override;
  Vector3 Normal(const Vector3& pos) const override;

  Vector3 normal;
  double offset;
};

inline Plane::Plane(const Surface& surface, const Vector3& n, double o)
    : SceneObject(surface), normal(n), offset(o) { }

inline Plane::~Plane() { }

class Scene {
 public:
  std::vector<ISect> Intersect(const Ray& ray) const;  // XXX: change to ISect*?

  std::vector<SceneObject*> things;
  std::vector<Light> lights;
  Camera camera;
};

}  // namespace raytracer

#endif  // UTILS_H_
