#include <Ps3Controller.h>
#include "Controller.h"

void Controller::update_state()
{
  this->_data = Ps3.data;
}