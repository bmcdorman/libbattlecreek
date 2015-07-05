#include "node.hpp"

#include <functional>
#include <sstream>

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
  
  std::shared_ptr<daylite::subscriber> _motor_states;
  std::shared_ptr<daylite::subscriber> _servo_states;
  std::shared_ptr<daylite::subscriber> _analog_states;
  std::shared_ptr<daylite::subscriber> _digital_states;
  
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


