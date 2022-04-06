#include "libs/sGeometry.hxx"

using namespace SME::Class;
using namespace SME::Util::Math;

TVectorTriangle::TVectorTriangle(const TVec3f &_a,
                                 const TVec3f &_b,
                                 const TVec3f &_c) {
  a = _a;
  b = _b;
  c = _c;
};

f32 TVectorTriangle::bearingAngleY(const TVec3f &a,
                                   const TVec3f &b) {
  return radiansToAngle(atan2f(b.x - a.x, b.z - a.z));
}

void TVectorTriangle::normal(bool normalize, TVec3f &out) {
  TVec3f vectorA(b.x - a.x, b.y - a.y, b.z - a.z);

  TVec3f vectorB(c.x - a.x, c.y - a.y, c.z - a.z);

  TVec3f vec;
  Vector3::cross(vectorA, vectorB, vec);
  if (normalize)
    Vector3::normalized(vec, out);
}

void TVectorTriangle::center(TVec3f &out) {
  out.set((a.x + b.x + c.x) / 3.0f, (a.y + b.y + c.y) / 3.0f,
          (a.z + b.z + c.z) / 3.0f);
}

f32 TVectorTriangle::yPosAtXZ(f32 x, f32 z) {
  TVec3f n;
  normal(false, n);
  return (-n.x * (x - a.x) - n.z * (z - a.z)) / n.y - a.y;
}