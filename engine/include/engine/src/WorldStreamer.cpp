#include "WorldStreamer.h"
#include <iostream>

namespace engine {

void WorldStreamer::SetPlayerPosition(float x, float y, float z) {
  playerPos_[0] = x; playerPos_[1] = y; playerPos_[2] = z;
}

void WorldStreamer::Update(float dt) {
  (void)dt;
  // TODO: load/unload chunks based on playerPos_
  std::cout << "[WorldStreamer] Player at (" 
            << playerPos_[0] << ", " 
            << playerPos_[1] << ", " 
            << playerPos_[2] << ")\n";
}

} // namespace engine
