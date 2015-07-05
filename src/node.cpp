#include "node.hpp"

#include <functional>
#include <sstream>

#include <daylite/spinner.hpp>

using namespace battlecreek;
using namespace std;
using namespace std::placeholders;

node *node::_singleton_self = 0;

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
  
  if(!(_set_motor_states_pub = _node->advertise("robot/set_motor_states"))) return false;
  if(!(_set_servo_states_pub = _node->advertise("robot/set_servo_states"))) return false;
  if(!(_set_analog_states_pub = _node->advertise("robot/set_analog_states"))) return false;
  if(!(_set_digital_states_pub = _node->advertise("robot/set_digital_states"))) return false;
  
  if(!(_motor_states_sub = _node->subscribe("robot/motor_states", bind(&node::motor_states_cb, this, _1, _2)))) return false;
  if(!(_servo_states_sub = _node->subscribe("robot/servo_states", bind(&node::servo_states_cb, this, _1, _2)))) return false;
  if(!(_analog_states_sub = _node->subscribe("robot/analog_states", bind(&node::analog_states_cb, this, _1, _2)))) return false;
  if(!(_digital_states_sub = _node->subscribe("robot/digital_states", bind(&node::digital_states_cb, this, _1, _2)))) return false;
  
  return true;
}

void node::set_analog_pullup(const uint8_t id, const bool pullup)
{
  
}

void node::set_digital_mode(const uint8_t id, const bool mode)
{
  
}

void node::set_motor_state(const uint8_t id, const bson_bind::motor_state &motor_state)
{
  _motor_states[id] = motor_state;
  _motor_states_dirty[id] = true;
  if(_auto_publish) publish();
}

void node::set_servo_position(const uint8_t id, const uint16_t position)
{
  
}

bool node::analog_pullup(const uint8_t id)
{
  
}

bool node::digital_mode(const uint8_t id)
{
  
}

bson_bind::motor_state node::motor_state(const uint8_t id)
{
  if(_auto_publish) publish();
  return _motor_states[id];
}

uint16_t node::servo_position(const uint8_t id)
{
  
}

void node::publish()
{
  using namespace daylite;
  using namespace bson_bind;
  
  {
    motor_states msg;
    array<option<bson_bind::motor_state> *, 4> motor_state_ptr = {
      &msg.m0, &msg.m1, &msg.m2, &msg.m3
    };
    for(uint8_t i = 0; i < _motor_states.size(); ++i)
    {
      if(!_motor_states_dirty[i]) continue;
      *motor_state_ptr[i] = some(_motor_states[i]);
    }
    _set_motor_states_pub->publish(msg.bind());
  }
  
  
  spinner::spin_once();
}

void node::node::motor_states_cb(const bson_t *msg, void *)
{
  using namespace bson_bind;
  
  {
    auto ms = motor_states::unbind(msg);
    _motor_states_dirty.fill(false);
    array<option<bson_bind::motor_state> *, 4> motor_state_ptr = {
      &ms.m0, &ms.m1, &ms.m2, &ms.m3
    };
    for(uint8_t i = 0; i < _motor_states.size(); ++i)
    {
      if(motor_state_ptr[i]->none()) continue;
      _motor_states[i] = motor_state_ptr[i]->unwrap();
    }
  }
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


