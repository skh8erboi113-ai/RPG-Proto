#include "Mesh.h"
#include <fstream>
#include <sstream>
#include <iostream>

namespace engine {

Mesh::Mesh()
  : vbh_(BGFX_INVALID_HANDLE),
    ibh_(BGFX_INVALID_HANDLE) {
  layout_.begin()
    .add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
    .end();
}

Mesh::~Mesh() {
  if (bgfx::isValid(vbh_)) bgfx::destroy(vbh_);
  if (bgfx::isValid(ibh_)) bgfx::destroy(ibh_);
}

bool Mesh::LoadFromOBJ(const std::string& path) {
  std::ifstream file(path);
  if (!file) {
    std::cerr << "[Mesh] Failed to open OBJ: " << path << "\n";
    return false;
  }

  std::vector<MeshVertex> tempVerts;
  std::vector<uint16_t> tempIndices;

  std::string line;
  while (std::getline(file, line)) {
    if (line.empty()) continue;
    std::istringstream iss(line);
    std::string tag;
    iss >> tag;

    if (tag == "v") {
      float x, y, z;
      iss >> x >> y >> z;
      tempVerts.push_back({x, y, z});
    } else if (tag == "f") {
      uint32_t i1, i2, i3;
      // Simple parser
      std::string s1, s2, s3;
      iss >> s1 >> s2 >> s3;
      auto parseIdx = [](const std::string& s) {
        return std::stoi(s.substr(0, s.find('/')));
      };
      i1 = parseIdx(s1);
      i2 = parseIdx(s2);
      i3 = parseIdx(s3);
      tempIndices.push_back(static_cast<uint16_t>(i1 - 1));
      tempIndices.push_back(static_cast<uint16_t>(i2 - 1));
      tempIndices.push_back(static_cast<uint16_t>(i3 - 1));
    }
  }

  vertices_ = std::move(tempVerts);
  indices_ = std::move(tempIndices);
  CreateBuffers();
  return true;
}

void Mesh::CreateBuffers() {
  if (bgfx::isValid(vbh_)) bgfx::destroy(vbh_);
  if (bgfx::isValid(ibh_)) bgfx::destroy(ibh_);

  vbh_ = bgfx::createVertexBuffer(
    bgfx::makeRef(vertices_.data(), (uint32_t)(vertices_.size() * sizeof(MeshVertex))),
    layout_
  );
  ibh_ = bgfx::createIndexBuffer(
    bgfx::makeRef(indices_.data(), (uint32_t)(indices_.size() * sizeof(uint16_t)))
  );
}

void Mesh::Submit(bgfx::ViewId viewId, bgfx::ProgramHandle program, const float* mtx) {
  if (!bgfx::isValid(vbh_) || !bgfx::isValid(ibh_)) return;

  bgfx::setTransform(mtx);
  bgfx::setVertexBuffer(0, vbh_);
  bgfx::setIndexBuffer(ibh_);
  bgfx::setState(BGFX_STATE_DEFAULT);
  bgfx::submit(viewId, program);
}

} // namespace engine
