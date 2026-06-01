#include "engine/Types.h"
#include <cstring>

namespace engine {

Mat4::Mat4() {
  std::memset(data, 0, sizeof(data));
  data[0] = data[5] = data[10] = data[15] = 1.0f;
}

Mat4 Mat4::Identity() {
  return Mat4();
}

Mat4 Mat4::Translate(f32 x, f32 y, f32 z) {
  Mat4 m;
  m.data[12] = x;
  m.data[13] = y;
  m.data[14] = z;
  return m;
}

Mat4 Mat4::Scale(f32 x, f32 y, f32 z) {
  Mat4 m;
  m.data[0] = x;
  m.data[5] = y;
  m.data[10] = z;
  return m;
}

Mat4 Mat4::RotateX(f32 angle) {
  Mat4 m;
  f32 c = std::cos(angle);
  f32 s = std::sin(angle);
  m.data[5] = c;   m.data[6] = -s;
  m.data[9] = s;   m.data[10] = c;
  return m;
}

Mat4 Mat4::RotateY(f32 angle) {
  Mat4 m;
  f32 c = std::cos(angle);
  f32 s = std::sin(angle);
  m.data[0] = c;   m.data[8] = s;
  m.data[8] = -s;  m.data[10] = c;
  return m;
}

Mat4 Mat4::RotateZ(f32 angle) {
  Mat4 m;
  f32 c = std::cos(angle);
  f32 s = std::sin(angle);
  m.data[0] = c;   m.data[1] = -s;
  m.data[4] = s;   m.data[5] = c;
  return m;
}

Vec4 Mat4::operator*(const Vec4& v) const {
  return Vec4(
    data[0] * v.x + data[4] * v.y + data[8] * v.z + data[12] * v.w,
    data[1] * v.x + data[5] * v.y + data[9] * v.z + data[13] * v.w,
    data[2] * v.x + data[6] * v.y + data[10] * v.z + data[14] * v.w,
    data[3] * v.x + data[7] * v.y + data[11] * v.z + data[15] * v.w
  );
}

Mat4 Mat4::operator*(const Mat4& m) const {
  Mat4 result;
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      f32 sum = 0.0f;
      for (int k = 0; k < 4; ++k) {
        sum += data[k * 4 + i] * m.data[j * 4 + k];
      }
      result.data[j * 4 + i] = sum;
    }
  }
  return result;
}

}  // namespace engine
