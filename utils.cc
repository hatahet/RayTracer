#include "utils.h"

namespace raytracer {

// Camera

Camera::Camera(const Vector3& position, const Vector3& look_at)
    : pos(position),
      forward((look_at - pos).Normal()),
       right(1.5 * (forward.Cross(Vector3(0, -1, 0))).Normal()),
       up(1.5 * (forward.Cross(right)).Normal()) { }

}  // namesace raytracer
