#pragma once

#include <cstdint>

namespace SystemCore
{
  // forward declaration because of ContextManager/MenuTileNavigation circular dependency
  class ContextManager;
}

namespace Display
{
  class MenuTileNavigation
  {
  public:
    MenuTileNavigation(SystemCore::ContextManager *ctx) : contextManager{ctx} {}
    void displayMenuNavigation();
    static constexpr uint16_t menuTileWidth = 12;

  private:
    SystemCore::ContextManager *contextManager;
  };
}