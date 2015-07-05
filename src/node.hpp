#ifndef _BATTLECREEK_NODE_HPP_
#define _BATTLECREEK_NODE_HPP_

#include <daylite/node.hpp>
#include <cstdint>
#include <vector>
#include <iostream>
#include <array>

#include "analog_states.hpp"
#include "digital_states.hpp"
#include "motor_states.hpp"
#include "servo_states.hpp"

namespace battlecreek
{
  class node
  {
  public:
    node();
    
    static node &ref()
    {
      if(!_singleton_self)
      {
        _singleton_self = new node();
        if(!_singleton_self->initialize())
        {
          std::cerr << "Failed to initialize daylite node!" << std::endl;
          delete _singleton_self;
          _singleton_self = 0;
        }
        
      }
      return *_singleton_self;
    }
    
    bool initialize();
    
    inline void set_auto_publish(const bool auto_publish) { _auto_publish = auto_publish; }
    inline bool auto_publish() const { return _auto_publish; }
    
    void set_analog_pullup(const uint8_t id, const bool pullup);
    void set_digital_mode(const uint8_t id, const bool mode);
    void set_motor_state(const uint8_t id, const bson_bind::motor_state &motor_state);
    void set_servo_position(const uint8_t id, const uint16_t position);
    
    bool analog_pullup(const uint8_t id);
    bool digital_mode(const uint8_t id);
    bson_bind::motor_state motor_state(const uint8_t id);
    uint16_t servo_position(const uint8_t id);
    
    void publish();
    
  private:
    
    
    void motor_states_cb(const bson_t *msg, void *);
    void servo_states_cb(const bson_t *msg, void *);
    void analog_states_cb(const bson_t *msg, void *);
    void digital_states_cb(const bson_t *msg, void *);
    
    
    
    static node *_singleton_self;
    
    bool _auto_publish;
    
    std::shared_ptr<daylite::node> _node;
    
    std::array<bson_bind::motor_state, 4> _motor_states;
    std::array<bool, 4> _motor_states_dirty;
    std::vector<uint16_t> _servos;
    
    std::shared_ptr<daylite::publisher> _set_motor_states_pub;
    std::shared_ptr<daylite::publisher> _set_servo_states_pub;
    std::shared_ptr<daylite::publisher> _set_analog_states_pub;
    std::shared_ptr<daylite::publisher> _set_digital_states_pub;
    
    std::shared_ptr<daylite::subscriber> _motor_states_sub;
    std::shared_ptr<daylite::subscriber> _servo_states_sub;
    std::shared_ptr<daylite::subscriber> _analog_states_sub;
    std::shared_ptr<daylite::subscriber> _digital_states_sub;
    
  };
}

#endif