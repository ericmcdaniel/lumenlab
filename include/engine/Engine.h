namespace Engine
{
  enum class State
  {
    GAME,
    INVALID
  };

  class Engine
  {
  public:
    State currentAction;

    Engine(State state = State::INVALID) : currentAction(state) {}
  };
}