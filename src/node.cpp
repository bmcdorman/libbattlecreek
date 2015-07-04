#include "node.hpp"

#include <functional>
#include <sstream>

using namespace battlecreek;
using namespace std;

node *node::_singleton_self = 0;

motor_state::motor_state(const _mode m, bool open_loop, const uint64_t position,
  const uint32_t velocity, const uint16_t power)
  : mode(m)
  , open_loop(open_loop)
  , position(position)
  , velocity(velocity)
  , power(power)
{
}

motor_state motor_state::off_motor_state()
{
  return motor_state(mode_off, false, 0, 0, 0);
}
  
motor_state motor_state::power_motor_state(const uint16_t power)
{
  return motor_state(mode_power, false, 0, 0, power);
}

motor_state motor_state::velocity_motor_state(const uint32_t velocity, const bool open_loop)
{
  return motor_state(mode_velocity, open_loop, 0, velocity, 0);
}

motor_state motor_state::position_motor_state(const uint64_t position, const uint32_t velocity,
  const bool open_loop)
{
  return motor_state(mode_position, open_loop, position, velocity, 0);
}

namespace
{
  string create_anonymous_name()
  {
    stringstream res;
    // FIXME: This is pitiful
    res << "battlecreek-" << (rand() % 100000U);
    return res.str();
  }
}

node::node()
  : _auto_publish(true)
  , _node(daylite::node::create_node(create_anonymous_name()))
{
}

bool node::initialize()
{
  if(!_node->join_daylite("127.0.0.1", 8374)) return false;
  
  std::shared_ptr<daylite::subscriber> _motor_states;
  std::shared_ptr<daylite::subscriber> _servo_states;
  std::shared_ptr<daylite::subscriber> _analog_states;
  std::shared_ptr<daylite::subscriber> _digital_states;
  if(!(_set_motor_states = _node->advertise("robot/set_motor_states"))) return false;
  if(!(_set_servo_states = _node->advertise("robot/set_servo_states"))) return false;
  if(!(_set_analog_states = _node->advertise("robot/set_analog_states"))) return false;
  if(!(_set_digital_states = _node->advertise("robot/set_digital_states"))) return false;
  
  // if(!(_motor_states = _node->subscribe("robot/motor_states", bind(&node::motor_states_cb, this)))) return false;
  // if(!(_servo_states = _node->subscribe("robot/servo_states", bind(&node::motor_states_cb, this)))) return false;
  // if(!(_analog_states = _node->subscribe("robot/analog_states", bind(&node::motor_states_cb, this)))) return false;
  // if(!(_digital_states = _node->subscribe("robot/digital_states", bind(&node::motor_states_cb, this)))) return false;
  
  return true;
}

void node::motor_states_cb(const bson_t *msg, void *)
{
}

void node::servo_states_cb(const bson_t *msg, void *)
{
  
}

void node::analog_states_cb(const bson_t *msg, void *)
{
  
}

void node::digital_states_cb(const bson_t *msg, void *)
{
  
}


