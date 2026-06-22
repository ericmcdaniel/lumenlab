#include "games/chain-reaction/ion-cannon.h"
#include "logger.h"

namespace Games::ChainReaction
{

  void IonCannon::dispatch()
  {
    ionPool.emplace_back(2); // remove hardcode when possible
    logf("New color dispatched");
  }

  void IonCannon::reset()
  {
    ionPool.clear();
  }

  const size_t IonCannon::shouldDispatch() const
  {
    return std::count_if(ionPool.begin(), ionPool.end(), [](const Ion &ion)
                         { return ion.isActive(); });
  }
}