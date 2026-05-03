#pragma once

#include <memory>
#include <vector>
#include "engine/Entity.hpp"


class Renderer {
public:

  void render(Entity& entity);
  void render(std::vector<std::shared_ptr<Entity>> entities);
};
