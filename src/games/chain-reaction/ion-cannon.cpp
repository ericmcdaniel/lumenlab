#include "games/chain-reaction/ion-cannon.h"

namespace Games::ChainReaction
{

  void IonCannon::dispatch()
  {
    ionPool.emplace_back(2); // remove hardcode when possible
  }

  void IonCannon::reset()
  {
    ionPool.clear();
  }

  const size_t IonCannon::isReady() const
  {
    return std::count_if(ionPool.begin(), ionPool.end(), [](const Ion &ion)
                         { return ion.isActive(); });
  }
}