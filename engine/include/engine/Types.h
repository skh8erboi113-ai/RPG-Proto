#pragma once

#include <cstdint>
#include <cmath>
#include <limits>
#include <array>

namespace engine {

using i8 = int8_t;
using i16 = int16_t;
using i32 = int32_t;
using i64 = int64_t;
using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;
using f32 = float;
using f64 = double;

struct alignas(16) Vec2 {
  f32 x, y;
  Vec2() : x(0), y(0) {}
  Vec2(f32 x, f32 y) : x(x), y(y) {}
  Vec2 operator+(const Vec2& v) const { return Vec2(x + v.x, y + v.y); }
  Vec2 operator-(const Vec2& v) const { return Vec2(x - v.x, y - v.y); }
  Vec2 operator*(f32 s) const { return Vec2(x * s, y * s); }
  f32 dot(const Vec2& v) const { return x * v.x + y * v.y; }
  f32 length() const { return std::sqrt(x * x + y * y); }
};

struct alignas(16) Vec3 {
  f32 x, y, z;
  Vec3() : x(0), y(0), z(0) {}
  Vec3(f32 x, f32 y, f32 z) : x(x), y(y), z(z) {}
  Vec3 operator+(const Vec3& v) const { return Vec3(x + v.x, y + v.y, z + v.z); }
  Vec3 operator-(const Vec3& v) const { return Vec3(x - v.x, y - v.y, z - v.z); }
  Vec3 operator*(f32 s) const { return Vec3(x * s, y * s, z * s); }
  f32 dot(const Vec3& v) const { return x * v.x + y * v.y + z * v.z; }
  Vec3 cross(const Vec3& v) const { return Vec3(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x); }
  f32 length() const { return std::sqrt(x * x + y * y + z * z); }
};

struct alignas(16) Vec4 {
  f32 x, y, z, w;
  Vec4() : x(0), y(0), z(0), w(1) {}
  Vec4(f32 x, f32 y, f32 z, f32 w) : x(x), y(y), z(z), w(w) {}
  Vec4(const Vec3& v, f32 w) : x(v.x), y(v.y), z(v.z), w(w) {}
  Vec4 operator+(const Vec4& v) const { return Vec4(x + v.x, y + v.y, z + v.z, w + v.w); }
  Vec4 operator-(const Vec4& v) const { return Vec4(x - v.x, y - v.y, z - v.z, w - v.w); }
  Vec4 operator*(f32 s) const { return Vec4(x * s, y * s, z * s, w * s); }
  f32 dot(const Vec4& v) const { return x * v.x + y * v.y + z * v.z + w * v.w; }
};

struct alignas(16) Mat4 {
  f32 data[16];
  Mat4();
  static Mat4 Identity();
  static Mat4 Translate(f32 x, f32 y, f32 z);
  static Mat4 Scale(f32 x, f32 y, f32 z);
  static Mat4 RotateX(f32 angle);
  static Mat4 RotateY(f32 angle);
  static Mat4 RotateZ(f32 angle);
  Vec4 operator*(const Vec4& v) const;
  Mat4 operator*(const Mat4& m) const;
};

struct PerfStats {
  f64 deltaTime = 0.0;
  u32 frameCount = 0;
  f64 totalTime = 0.0;
  f32 avgFPS = 0.0f;
  u32 peakMemory = 0;
};

}  // namespace engine
