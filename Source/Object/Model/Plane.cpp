#include "Object/Model/Plane.h"

#include <iostream>
#include <limits>

namespace Raytracer {

std::optional<SurfaceRecord> PlaneModel::RayCast(const Ray& Ray, const TRange<float>& Range) const
{
    const float D = dot(Ray.Direction, Normal);

    if (std::abs(D) <= std::numeric_limits<float>::epsilon()) {
        return std::nullopt;
    }

    const float3 O = std::abs(length2(Ray.Origin)) <= std::numeric_limits<float>::epsilon() ? float3 { 0.0001f, 0.0001f, 0.0001f } : Ray.Origin;

    const float T = -dot(O - GetLocation(), Normal) / D;
    if (T <= 0 || !Range.Included(T)) {
        return std::nullopt;
    }

    const bool Front = D < 0;
    return SurfaceRecord { .T = T, .IsFront = Front, .Position = Ray.P(T), .Normal = Normal, .Radiance = GetColor(), .Mat = GetMaterial() };
}

}
