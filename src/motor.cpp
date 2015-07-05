#include "battlecreek/motor.hpp"
#include "node.hpp"

using namespace battlecreek;

motor::motor(const uint8_t port)
  : _port(port)
  , _origin_position(0)
{
}

void motor::power(const int16_t amt)
{
  // motor_state s;
  // s.power = some(amt);
  // node::ref().set_motor_state(_port, s);
}

void motor::velocity(const bool open_loop, const int32_t ticks_per_second)
{
  
}

void motor::position(const bool open_loop, const int32_t ticks_per_second, const int32_t desired_position)
{
  
}

int16_t motor::power() const
{
  
}

int32_t motor::velocity() const
{
  
}

int32_t motor::position() const
{
  
}

bool motor::open_loop() const
{
  
}

uint8_t motor::port() const
{
  return _port;
}

void motor::clear_position()
{
}