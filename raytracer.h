#ifndef RAYTRACER_H_
#define RAYTRACER_H_
#pragma once

#include <vector>

#include "color.h"
#include "ppm.h"
#include "utils.h"

namespace raytracer {

class RayTracer {
 public:
  RayTracer(int width, int height);
  ~RayTracer();

 private:
  std::vector<ISect> GetIntersections(const Ray& ray, const Scene& scene) const;
  double CastTestRay(const Ray& ray, const Scene& scene) const;
  Color TraceRay(const Ray& ray, const Scene& scene, int depth) const;
  Color GetNaturalColor(const SceneObject& thing, const Vector3& pos,
                        const Vector3& normal, const Vector3& rd,
                        const Scene& scene) const;
  Color GetReflectionColor(const SceneObject& thing, const Vector3& pos,
                           const Vector3& rd, const Scene& scene,
                           int depth) const;
  Color Shade(const ISect& isect, const Scene& scene, int depth) const;
  double RecenterX(double x) const;
  double RecenterY(double y) const;
  Vector3 GetPoint(double x, double y, const Camera& camera) const;
  void Render(const Scene& scene);

  int width_;
  int height_;
  PpmFile image_;
};

inline RayTracer::RayTracer(int width, int height)
    : width_(width), height_(height), image_(height_, width_) { }

inline RayTracer::~RayTracer() { }

}

#endif  // RAYTRACER_H_
